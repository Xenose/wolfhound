
try:
    import git

    _IMPORTED_GIT=True
except ImportError:
    _IMPORTED_GIT=False

from common.params import params_c



def execute(params: params_c):
    if not _IMPORTED_GIT:
        print("Failed to pull in python git!")
        return

    print("Hello!")
    #repo = git.Repo(params.sh.session["home"])
    #branch = repo.active_branch

    #print(f"\n {branch}")

    # if "inrdev" == branch.name:
    #     print("On 'inrdev' branch. Pulling latest changes and committing...")
    #     # print(repo.git.pull())
    #     # print(repo.git.add(all=True))

    #     # Inrdev comment as IN Rapid DEVelopment branch
    #     repo.index.commit("inrdev")
    #     print(repo.git.push())
    # else:
    #     print(f"Sorry [ {branch} ] is not the 'inrdev' branch, aborting...")
