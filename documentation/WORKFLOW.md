
# WORKFLOW.md - CI/CD Workflow for R-Type Project

## Overview
This document outlines the Continuous Integration and Continuous Deployment (CI/CD) workflow for the **R-Type** project. It uses **GitHub Actions** to automate the process of building, testing, releasing, and mirroring the repository.

### Workflow Triggers
The workflow is triggered by two main events:
- **pull_request** on the `main` branch.
- **push** on the `main` branch after a pull request is merged.

### Workflow Structure
The workflow is structured in jobs that perform tasks like building the project, running tests, releasing builds, and mirroring the repository.

### Jobs and Steps
Below is a detailed breakdown of each job in the workflow.

## ASCII Diagram of Workflow:

```
                            +--------------------------+
                            |    pull_request (main)   |
                            +--------------------------+
                                          |
                                          v
                            +----------------------------+
                            |    build_cross_platform    |
                            |   (Installs dependencies,  |
                            |     builds the project)    |
                            +----------------------------+
                                          |
                                          v
                            +----------------------------+
                            |     check_compilation      |
                            |   (Verifies the build by   |
                            |    compiling with make)    |
                            +----------------------------+
                                          |
                                          v
                            +----------------------------+
                            |  release_mode_test         |
                            | (Sets up and tests the     |
                            |  release mode)             |
                            +----------------------------+
                                          |
                                          v
                            +---------------------------+
                            |       push_to_mirror      |
                            | (Mirrors the repo after   |
                            |  tests pass)              |
                            +---------------------------+

                            +----------------------------+
                            |        push (main)         |
                            |  (After PR merge on main)  |
                            +----------------------------+
                                          |
                                          v
                            +----------------------------+
                            |    create_linux_release    |
                            | (Creates and uploads Linux |
                            |       release assets)      |
                            +----------------------------+
```

### Job Breakdown:

1. **build_cross_platform**:
   - **Triggered by**: `pull_request` on `main`
   - **Runs on**: Ubuntu
   - **Steps**:
     - Checks out the code.
     - Installs basic dependencies (e.g., `build-essential`) to build the project.

2. **check_compilation**:
   - **Triggered by**: Completion of `build_cross_platform`
   - **Runs on**: Ubuntu
   - **Steps**:
     - Checks out the code.
     - Installs all necessary libraries (`libboost-all-dev`, `libsfml-dev`, `libconfig++-dev`).
     - Runs `make` to build the project.
     - Verifies that the required binaries (`r-type_client`, `r-type_server`) are created.

3. **release_mode_test**:
   - **Triggered by**: `pull_request` on `main`
   - **Runs on**: Ubuntu
   - **Steps**:
     - Checks out the code.
     - Sets up a test environment to simulate the release mode using `expect` to interact with the installer.
     - Verifies that the binaries in release mode are created (`r-type_client`, `r-type_server`).

4. **create_linux_release**:
   - **Triggered by**: `push` on `main` after a pull request is merged
   - **Runs on**: Ubuntu
   - **Steps**:
     - Checks out the code.
     - Creates an archive (`tar.gz`) of the release build in `release_archive`.
     - Uploads the release assets to GitHub using `upload-release-asset`.

5. **push_to_mirror**:
   - **Triggered by**: Completion of `release_mode_test`
   - **Runs on**: Ubuntu
   - **Steps**:
     - Checks out the code.
     - Mirrors the repository to a different target repository using the `pixta-dev/repository-mirroring-action`.

## Conclusion:
This CI/CD workflow ensures that each pull request on the `main` branch is tested and compiled properly. Once a pull request is merged, a new release is automatically created and uploaded, and the repository is mirrored to an external location.
