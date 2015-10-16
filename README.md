# Drude Testing

This is a sample vanila Drupal 7 installation preconfigured for use with Drude.  
Sample Behat tests also included.

## Instructions (Mac and Windows)

**On Windows** you will need a Linux-type shell. Install [Babun](http://babun.github.io/) before proceeding and run all commands in it.  
Instructions were not tested with other shells on Windows.

1. Install `dsh` (Drude Shell)

    ```
    sudo curl -L https://raw.githubusercontent.com/blinkreaction/drude/master/bin/dsh  -o /usr/local/bin/dsh
    sudo chmod +x /usr/local/bin/dsh
    ```

2. Create the `<Projects>` directory
    
    ```
    mkdir Projects
    cd Projects
    ```

3. Install Drude's prerequisites (vagrant, virtualbox, boot2docker-vagrant)

    ```
    dsh install prerequisites
    dsh install boot2docker
    ```
   
4. Clone this repo into the Projects directory

    ```
    git clone https://github.com/blinkreaction/drude-testing.git
    cd drude-testing
    ```

5. Set up `settings.local.php` in `sites/default`
 
    ```
    cd docroot/sites/default
    cp example.settings.local.php settings.local.php
    ```

6. Install Drupal
 
    ```
    dsh drush si -y
    ```

7. Add `192.168.10.10  hello-world.drude` to your hosts file

8. Point your browser to

    ```
    http://hello-world.drude
    ```

## More automation with 'dsh init'

Site provisioning can be automated using `dsh init`, which calls the shell script in [.drude/scripts/drude-init.sh](.drude/scripts/drude-init.sh).  
This script is meant to be modified per project. The one in this repo will give you a good starting point.

Some common tasks that can be handled by the init script:

- initialize local settings files (Docker Compose, Drupal, Behat, etc.)
- import DB / perform a site install
- compile Sass
- run DB updates, revert features, clear cached, etc.
- apply local settings (e.g. enable/disable modules, updates variable values)
- run Behat tests available in the repo

Try it - run in this project repo:

    dsh init
