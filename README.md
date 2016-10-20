# Docksal powered Drupal 7 Installation

This is a sample vanilla Drupal 7 installation pre-configured for use with Docksal.  

Features:

- Vannila Drupal 7
- `fin init` example
- Drupal multisite example
- Behat setup example and sample tests

## Setup instructions

### Step #1: Docksal environment setup

**This is a one time setup - skip this if you already have a working Docksal environment.**  

Follow [Docksal environment setup instructions](https://github.com/docksal/docksal/blob/develop/docs/env-setup.md)
   
### Step #2: Project setup

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

Example of running Behat tests: 

```
fin behat features/blackbox.feature
```


## Drupal multisite example

There is an additional site configured in this project: `anothersite.drupal7.docksal`

To have it installed during `fin int` 

1. Uncomment the following block in [.docksal/commands/init](.docksal/commands/init):

    ```
    # Multisite - install an additional site
    site_install_anothersite
    ```

2. Run `fin init` again
3. **On Windows** add another domain mapping to your hosts file 

```
192.168.64.100	anothersite.drupal7.docksal
```
