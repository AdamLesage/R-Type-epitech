
![Logo of the project](https://shmups.wiki/images/thumb/6/64/R-Type_Logo.png/500px-R-Type_Logo.png)

# R-Type Reproduction
> This project is part of the 3rd year of the Epitech curriculum.

A reproduction of the famous game R-Type, made in C++.

To see more about R-Type, you can visit the [R-Type Wikipedia page](https://fr.wikipedia.org/wiki/R-Type).

## Installing / Getting started

There are two ways to install and run the project, depending on whether you are developing or using the software as a regular user.

### For Developers (Development Mode)

To install the project in development mode, you can clone the repository and compile it with the `Makefile`:

```shell
git clone git@github.com:AdamLesage/R-Type-epitech.git
cd R-Type-epitech
make
```

This will create an executable file called `rtype` in the `build` directory.

### For Users (Production Mode)

If you want to install and use the software as a regular user, simply download the latest release from the [Releases](https://github.com/AdamLesage/R-Type-epitech/releases) section on GitHub.

For **Linux** users:
1. Download the Linux release from the release page.
2. Make the installer executable:
    ```shell
    chmod +x linux_installer.sh
    ```
3. Run the installer:
    ```shell
    ./linux_installer.sh
    ```

For more details on the installation, check the documentation file: `./documentation/LINUX_INSTALL.md`.

For **Windows** users:

1. Download the Windows release from the release page.
2. Right click on the windows_installer.exe and run it as an administrator
3. Then answer the question (You need to say yes to install all the dependancies to run the project)
4. The project will build and will be ready to use

more details on the installation, check the documentation file: `./documentation/WINDOWS_INSTALL.md`.

## See more documentation

1. [Technical Comparative Study](documentation/TECHNICAL_COMPARATIVE_STUDY.md) (see doc: `./documentation/TECHNICAL_COMPARATIVE_STUDY.md`)
2. [Protocol](documentation/PROTOCOL.md) (see doc: `./documentation/PROTOCOL.md`)
3. [Workflow](documentation/WORKFLOW.md) (see doc: `./documentation/WORKFLOW.md`)
4. [Contributing](CONTRIBUTING.md) (see doc: `./CONTRIBUTING.md`)
5. [Windows Installation](documentation/WINDOWS_INSTALL.md) (see doc: `./documentation/WINDOWS_INSTALL.md`)

To have a clear representation of the project, you can check the file `./documentation/docs/html/index.html` which is the doxygen documentation of the project.

## Developing

This section is already mentioned above under development mode. For more details, refer to the `start_project.sh` or follow the manual build process using `make`.

### Deploying / Publishing

The deployment process is as simple as downloading the release package for the respective platform and running the installer. Further deployment instructions may be added in the future.

## Features

List of features to be added.

## Contributing

We welcome contributions! If you'd like to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome.

For more details about contributing (code style, guidelines, etc.), check the `CONTRIBUTING.md` file.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
