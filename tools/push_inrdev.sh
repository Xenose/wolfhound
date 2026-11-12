#!/bin/bash
# This script is only used to push "in rapid development" branch only.

set -e

prompt="Write a short commit summary for the changes below. No prefixes like chore/feat, no echoing instructions, strictly the summary:"
branch=$(git symbolic-ref --short HEAD)

model_path="${HOME}/.cache/models/qwen2.5-coder-7b-instruct-q4_k_m.gguf"
model_url="https://huggingface.co/Qwen/Qwen2.5-Coder-7B-Instruct-GGUF/resolve/main/qwen2.5-coder-7b-instruct-q4_k_m.gguf"

if [ "inrdev" = "${branch}" ]; then
    echo "On 'inrdev' branch."
    git add -A

    # Check if there are any changes (staged or unpushed)
    if ! git diff --cached --quiet; then
        mkdir -pv ~/.cache/models

        if [[ ! -f "${model_path}" ]]; then
            echo "Downloading AI model for commit messages..."

            curl -L -o "${model_path}" "${model_url}" 
        fi

        tmp_file="/tmp/.commit_message_$$.txt"
        tmp_prompt="/tmp/prompt_$$.txt"

        {
            echo "### Instruction:"
            echo "${prompt}"
            echo ""
            echo "### Diff:"
            git diff --cached
            echo ""
            echo "### Response:"
        } > "${tmp_prompt}"

        llama-cli \
            -m "${model_path}" \
            -f "${tmp_prompt}" \
            -n 8096 \
            -st \
            -t $(nproc) \
            --temp 0.2 \
            -o "${tmp_file}"

        MSG="$(awk '/^Assistant:/{flag=1; next} flag {print}' "${tmp_file}" | sed -e '/^[[:space:]]*$/N;/^\n$/D')"
        # Strip any stray conventional prefixes
        MSG="$(echo "${MSG}" | sed -E 's/^[a-zA-Z0-9_-]+(\([a-zA-Z0-9_-]+\))?: *//')"
        # Strip surrounding markdown backticks if the model adds them
        MSG="$(echo "${MSG}" | sed 's/^[[:space:]]*`//;s/`[[:space:]]*$//')"

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
            read -p "Do you want to proceed with this commit and push? (y/N) " -n 1 -r
            echo

            if [[ ! $REPLY =~ ^[Yy]$ ]]; then
                echo "Commit and push aborted by user."
                exit 0
            fi

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
