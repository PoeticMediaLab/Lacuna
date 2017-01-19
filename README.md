# Docksal powered Drupal 7 Installation

This is a sample vanilla Drupal 7 installation pre-configured for use with Docksal.  

Features:

- Vanilla Drupal 7
- `fin init` example

## Setup instructions

### Step 1: Docksal environment setup

**This is a one time setup - skip this if you already have a working Docksal environment.**  

Follow [Docksal environment setup instructions](https://github.com/docksal/docksal/blob/develop/docs/env-setup.md)
   
### Step 2: Project setup

1. Clone this repo into your Projects directory

    ```
    git clone https://github.com/docksal/drupal7.git
    cd drupal7
    ```

2. Initialize the site

    This will initialize local settings and install the site via drush

    ```
    fin init
    ```

3. **On Windows** add `192.168.64.100  drupal7.docksal` to your hosts file

4. Point your browser to

    ```
    http://drupal7.docksal
    ```


## More automation with 'fin init'

Site provisioning can be automated using `fin init`, which calls the shell script in [.docksal/commands/init](.docksal/commands/init).  
This script is meant to be modified per project.

Some common tasks that can be handled in the init script:

- initialize local settings files for Docker Compose, Drupal, Behat, etc.
- import DB or perform a site install
- compile Sass
- run DB updates, revert features, clear caches, etc.
- enable/disable modules, update variables values
- run Behat tests
