# Drude Testing

This is a sample vanila Drupal 7 installation preconfigured for use with Drude.  
Sample Behat tests also included.

## Instructions (Mac and Windows)

**On Windows** you will need a Linux-type shell. Install [Babun](http://babun.github.io/) before proceeding and run all commands in it.  
Instructions were not tested with other shells on Windows.

1. Create directory structure (e.g. in your home directory)
    
    ```
    mkdir -p Projects/drude-testing
    cd drude-testing
    ```

2. Install `dsh` (Drude Shell)

    ```
    sudo curl -L https://raw.githubusercontent.com/blinkreaction/drude/develop/bin/dsh  -o /usr/local/bin/dsh
    sudo chmod +x /usr/local/bin/dsh
    ```

3. Install Drude and prerequisites (latest dev version)

    ```
    DRUDE_BRANCH=develop B2D_BRANCH=develop dsh install
    ```
    
4. In the end you will be prompted to relaunch you shell and run:

    ```
    dsh up
    ```

5. Install Drupal

    ```
    dsh drush si -y
    ```

6. Point your browser to

    ```
    http://hello-world.drude
    ```

## More automation with 'dsh init'

Site provisioning can be automated using `dsh init`, which calls the shell script in [.drude/scripts/drude-init.sh](.drude/scripts/drude-init.sh).  
This script is meant to be modified per project. The one in this repo will give you a good starting point.

Some commond tasks that can be handled by the init script:

- initialize local settings files (Docker Compose, Drupal, Behat, etc.)
- import DB / perform a site install
- compile Sass
- run DB updates, revert features, clear cached, etc.
- apply local settings (e.g. enable/disable modules, updates variable values)
- run Behat tests available in the repo

Try it - run in this project repo:

    dsh init
