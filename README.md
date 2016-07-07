# Drude powered Drupal 7 Installation

This is a sample vanilla Drupal 7 installation pre-configured for use with Drude.  

Features:

- Vannila Drupal 7
- `dsh init` example
- Drupal multisite example
- Behat setup example and sample tests

## Setup instructions

### Step #1: Drude environment setup

**This is a one time setup - skip this if you already have a working Drude environment.**  

Follow [Drude environment setup instructions](https://github.com/blinkreaction/drude/blob/master/docs/drude-env-setup.md)
   
### Step #2: Project setup

1. Clone this repo into your Projects directory

    ```
    git clone https://github.com/blinkreaction/drude-d7-testing.git
    cd drude-d7-testing
    ```

2. Initialize the site

    This will initialize local settings and install the site via drush

    ```
    dsh init
    ```

3. **On Windows** add `192.168.10.10  drupal7.drude` to your hosts file

4. Point your browser to

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
Uncomment selenium service in `docker-compose.yml` and it's link in `web` service. 

```yml
# Web node
web:
  ...
  links:
    - cli
    - browser
...
# selenium2 node
# Uncomment the service definition section below and the link in the web service above to start using selenium2 driver for Behat tests requiring JS support.
browser:
  hostname: browser
  image: selenium/standalone-chrome
  ports:
    - "4444"
  environment:
    - DOMAIN_NAME=drude-d7-testing.browser.docker
```

Run `dsh up` to have `browser` service up and running.

Then run Behat tests: 

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
