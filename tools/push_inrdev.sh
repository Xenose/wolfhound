#!/bin/bash
# This script is only used to push "in rapid development" branch only.

set -e

prompt="Generate a Git commit message for the changes below. Format the output with a short conventional commit title line (e.g., chore(gitignore): ...), followed by a blank line, followed by a concise bulleted list of changes. Output ONLY the commit message text. Do not include any explanations, summaries, headers, or conversational text:"
branch=$(git symbolic-ref --short HEAD)

if [ "inrdev" = "${branch}" ]; then
    echo "On 'inrdev' branch. Pulling latest changes and committing..."

    # Stash any local uncommitted changes so git pull doesn't fail
    git stash
    git pull --rebase
    git stash pop || true

    git add -A

    # Check if there are any changes (staged or unpushed)
    if ! git diff --cached --quiet; then
        mkdir -pv ~/.cache/models

        # TODO make this configurable.
        if [[ ! -f ~/.cache/models/qwen2.5-0.5b-instruct.gguf ]]; then
            echo "Downloading AI model for commit messages..."

            curl -L -o ~/.cache/models/qwen2.5-0.5b-instruct.gguf \
                https://huggingface.co/Qwen/Qwen2.5-0.5B-Instruct-GGUF/resolve/main/qwen2.5-0.5b-instruct-q4_k_m.gguf
        fi

        tmp_file="/tmp/.commit_message_$$.txt"
        tmp_prompt="/tmp/prompt_$$.txt"

        {
            echo "${prompt}"
            echo ""
            git diff --cached -- . ':!tools/push_inrdev.sh'
        } > "${tmp_prompt}"

        llama-cli \
            -m ~/.cache/models/qwen2.5-0.5b-instruct.gguf \
            -f "${tmp_prompt}" \
            -n 8096 \
            -st \
            -t $(nproc) \
            --temp 0.5 \
            -o "${tmp_file}"

        MSG="$(awk '/^Assistant:/{flag=1; next} flag {print}' "${tmp_file}" | sed -e '/^[[:space:]]*$/N;/^\n$/D')"
        rm -f "${tmp_file}" "${tmp_prompt}"

        # Fallback if the model didn't output quotes
        if [ -z "${MSG}" ]; then
            MSG="inrdev: update changes"
        else
            MSG="$(echo -e "${MSG}\n\nAuto Generated git commit message by llama-cpp, errors might happen!")"
        fi

        if [ "${NO_PUSH:-0}" -eq 1 ]; then
            echo "--- Generated Commit Message ---"
            echo "${MSG}"
            echo "--------------------------------"
        else
            git commit -m "${MSG}"
            git push origin "${branch}"
        fi
    else
        echo "No staged changes to commit."
    fi
else
    echo "You are not on the 'inrdev' branch. Aborting push."
    exit 1
fi
