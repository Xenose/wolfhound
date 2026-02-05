import git


def execute(cmd, args, session, state):
    repo = git.Repo(session["home"])
    branch = repo.active_branch

    print("\n")

    if "inrdev" == branch.name:
        print("On 'inrdev' branch. Pulling latest changes and committing...")
        print(repo.git.pull())
        print(repo.git.add(all=True))

        # Inrdev comment as IN Rapid DEVelopment branch
        repo.index.commit("inrdev")
        print(repo.git.push())
    else:
        print(f"Sorry [ {branch} ] is not the 'inrdev' branch, aborting...")
