# Drude Testing

This is a sample vanila Drupal 7 installation preconfigured for use with Drude.  
Sample Behat tests also included.

## Instructions (Mac)

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
