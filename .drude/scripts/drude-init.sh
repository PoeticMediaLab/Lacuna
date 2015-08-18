#!/bin/bash
set -e

# Set to the appropriate site directory
SITE_DIRECTORY='default'
# Set to the appropriate site directory
SITE_DOMAIN='hello-world.drude'
# Set to the appropriate site alias for the DB source
#SOURCE_ALIAS='@none'

# Console colors
red='\033[0;31m'
green='\033[0;32m'
yellow='\033[1;33m'
NC='\033[0m'

# Get project root directory
GIT_ROOT=$(git rev-parse --show-toplevel)
if [[ -z $GIT_ROOT  ]]; then exit -1; fi

# Set repo root as working directory.
cd $GIT_ROOT

# Check whether shell is interactive (otherwise we are running in a non-interactive script environment)
is_tty ()
{
	[[ "$(/usr/bin/tty || true)" != "not a tty" ]]
}

# Yes/no confirmation dialog with an optional message
# @param $1 confirmation message
_confirm ()
{
	# Skip checks if not a tty
	if ! is_tty ; then return 0; fi

	while true; do
		read -p "$1 [y/n]: " answer
		case $answer in
			[Yy]|[Yy][Ee][Ss] )
				break
				;;
			[Nn]|[Nn][Oo] )
				exit 1
				;;
			* )
				echo 'Please answer yes or no.'
		esac
	done
}

# Copy a settings file from $source to $dest
# Skips if the $dest already exists.
_copy_settings_file()
{
  local source=${1}
  local dest=${2}

  if [[ ! -f $dest ]]; then
    echo -e "${green}Copying ${dest}...${NC}"
    cp $source $dest
  else
    echo -e "${yellow}${dest} already in place${NC}"
  fi
}

# Copy settings files
init_settings ()
{
  cd $GIT_ROOT

  _copy_settings_file 'docker-compose.yml.dist' 'docker-compose.yml'
  #_copy_settings_file "docroot/sites/example.sites.local.php" "docroot/sites/sites.local.php"
  _copy_settings_file "docroot/sites/${SITE_DIRECTORY}/example.settings.local.php" "docroot/sites/${SITE_DIRECTORY}/settings.local.php"
}

# Install the site
site_install ()
{
  cd $GIT_ROOT
  cd docroot
  # We disable email sending here so site-install does not return an error
  dsh exec 'PHP_OPTIONS="-d sendmail_path=`which true`" drush site-install -y'
}


# Import database from the source site alias
db_import ()
{
  #_confirm "Do you want to import DB from ${SOURCE_ALIAS}?"

  cd $GIT_ROOT
  cd docroot
  dsh drush -l ${SITE_DOMAIN} sql-sync ${SOURCE_ALIAS} @self -y
}

# Misc drush commands to bring DB up-to-date
db_updates ()
{
  cd $GIT_ROOT
  echo -e "${yellow}Applying DB updates...${NC}"
  cd docroot
  set -x

  dsh drush -l ${SITE_DOMAIN} status
  dsh drush -l ${SITE_DOMAIN} updb -y
  dsh drush -l ${SITE_DOMAIN} fr-all -y
  dsh drush -l ${SITE_DOMAIN} cc all
  dsh drush -l ${SITE_DOMAIN} cron -v

  set +x
}

# Local adjustments
local_settings ()
{
  cd $GIT_ROOT
  echo -e "${yellow}Applying local settings...${NC}"
  cd docroot
  set -x

  dsh drush -l ${SITE_DOMAIN} en stage_file_proxy -y

  set +x
}

# Compile Sass
compass_compile ()
{
  cd $GIT_ROOT
  echo -e "${yellow}Compiling Sass...${NC}"
  set -x

  #cd docroot/sites/all/themes/<themename>
  #dsh exec bundle install
  #dsh exec bundle exec compass compile

  set +x
}

# Initialize local Behat settings
init_behat ()
{
  cd $GIT_ROOT

  _copy_settings_file 'tests/behat/behat.yml.dist' 'tests/behat/behat.yml'
}

# Run basic Behat validation tests
run_behat ()
{
  cd $GIT_ROOT

  echo -e "${yellow}Launching Behat validation tests...${NC}"
  cd tests/behat
  dsh behat --format=pretty --out=std --format=junit --out=junit features/drush-si-validation.feature
}

# Project initialization steps
init_settings
dsh reset
# Give MySQL some time to start before importing the DB
sleep 5
site_install
#db_import
#db_updates
#local_settings
#compass_compile
init_behat
run_behat

echo -e "${green}All done!${NC}"
echo -e "${green}Add ${SITE_DOMAIN} to your hosts file (/etc/hosts), e.g.:${NC}"
echo -e "192.168.10.10  ${SITE_DOMAIN}"
echo -e "${green}Open http://${SITE_DOMAIN} in your browser to verify the setup.${NC}"
