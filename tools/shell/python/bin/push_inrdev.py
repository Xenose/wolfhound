import git


def execute(cmd, args, session, state):
    repo = git.Repo(session["home"])
    branch = repo.active_branch

    print("\n")

    if "inrdev" == str(branch):
        print("On 'inrdev' branch. Pulling latest changes and committing...")
        print(repo.git.pull())
        print(repo.git.add(all=True))
        print(repo.index.commit("inrdev"))
        print(repo.git.push())
    else:
        print(f"Sorry [ {branch} ] is not the 'inrdev' branch, aborting...")
