<?php

# Docker DB connection settings.
$databases = array (
  'default' =>
    array (
      'default' =>
        array (
          'database' => 'site1',
          'username' => getenv('DB_1_ENV_MYSQL_USER'),
          'password' => getenv('DB_1_ENV_MYSQL_PASSWORD'),
          'host' => getenv('DB_1_PORT_3306_TCP_ADDR'),
          'port' => '',
          'driver' => 'mysql',
          'prefix' => '',
        ),
    ),
);

# File system settings.
$conf['file_temporary_path'] = '/tmp';
# Workaround for permission issues with NFS shares in Vagrant
$conf['file_chmod_directory'] = 0777;
$conf['file_chmod_file'] = 0666;
