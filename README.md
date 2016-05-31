# Drude powered Drupal 7 Installation

This is a sample vanilla Drupal 7 installation preconfigured for use with Drude.  
Includes Sample Behat tests.

## Instructions (Mac and Windows)

**On Windows** you will need a Linux-type shell. Install [Babun](http://babun.github.io/) before proceeding and run all commands in it.  
Instructions were not tested with other shells on Windows.

1. Install `dsh` (Drude Shell)

    ```
    sudo curl -L https://raw.githubusercontent.com/blinkreaction/drude/master/bin/dsh -o /usr/local/bin/dsh
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
    git clone https://github.com/blinkreaction/drude-d7-testing.git
    cd drude-d7-testing
    ```

5. Initialize the site

    This will initialize local settings and install the site via drush

    ```
    dsh init
    ```

6. **On Windows** add `192.168.10.10  drupal7.drude` to your hosts file

7. Point your browser to

    ```
    http://drupal7.drude
    ```


## More automation with 'dsh init'

Site provisioning can be automated using `dsh init`, which calls the shell script in [.drude/commands/init](.drude/commands/init).  
This script is meant to be modified per project. The one in this repo will give you a good example of advanced init script.

Some common tasks that can be handled by the init script:

- initialize local settings files for Docker Compose, Drupal, Behat, etc.
- import DB or perform a site install
- compile Sass
- run DB updates, revert features, clear caches, etc.
- enable/disable modules, update variables values
- run Behat tests


## Behat test examples

Behat tests are stored in [tests/behat](tests/behat). 
Run Behat tests: 

```
dsh behat
```


## Drupal multisite example

There are two additional sites configured in this project:

 - drupal7-site1.drude
 - drupal7-site2.drude

To install them 

1. Uncomment the following block in [.drude/commands/init](.drude/commands/init):

    ```
    # Uncomment line below to install site 1
    db_create 'site1' && site_install 'drupal7-site1.drude'
    # Uncomment line below to install site 2
    db_create 'site2' && site_install 'drupal7-site2.drude'
    ```

2. Run `dsh init` again
3. **On Windows** add both domains to your hosts file 

```
192.168.10.10	drupal7-site1.drude drupal7-site2.drude
```
