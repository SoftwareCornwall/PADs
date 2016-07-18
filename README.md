# PADs across Cornwall
<<<<<<< HEAD
This repo contains the back-end stuff.

Dependencies:
Apache 2
MySQL
Slim
Twig-view

To create the database, run db_create.php.
To create the tables in the database, run tables_create.php.
To create dummy data, run tables_fill.php
To delete all the dummy data in the database, run tables_destroy.php

=======
The master branch is outdated. Only completely working iterations will be merged to it. For latest stuff, check out the develop branch

This repo contains the back-end stuff.

Dependencies:  
* MySQL  
* Slim  
* Twig-view  


To create the database, run db_create.php.

To create the tables in the database, run tables_create.php.

To create dummy data, run tables_fill.php

To delete all the dummy data in the database, run tables_destroy.php


>>>>>>> refs/remotes/origin/master
Ensure that you update the username and password variables in both db_create and db_connect to match the username and password chosen for your database. We simply used "root" and "password".

To set up the Apache stuff, I strongly advise you cheat and use XAMPP. Otherwise, you set up apache at your own risk.

To set everything up, follow these commands:
<<<<<<< HEAD
sudo apt-get install php5-common libapache2-mod-php5 php5 cli
sudo apt-get install apache2
sudo apt-get install mysql-server
sudo a2enmod rewrite

Install slim
sudo composer require slim/slim
Install composer and twig in working dir

Password is empty, unless you set one in install.
=======

sudo apt-get install php5-common libapache2-mod-php5 php5 cli

sudo apt-get install apache2

sudo apt-get install mysql-server

sudo a2enmod rewrite


Install slim

sudo composer require slim/slim

Install composer and twig in working dir


Password is empty, unless you set one in install.

>>>>>>> refs/remotes/origin/master
mysql -u root -p

mysql>CREATE DATABASE <my_db_name>;

//dev config: /etc/apache2/sites-enabled/000-default.conf
<<<<<<< HEAD
  ServerAdmin webmaster@localhost
  DocumentRoot /home/pi/PADs/web
  
  <Directory />
    Order allow, deny
    Allow from all
    Require all granted
    AllowOverride All #this allows .htaccess
=======

  ServerAdmin webmaster@localhost
  
  DocumentRoot /home/pi/PADs/web
  
  
  <Directory />
  
    Order allow, deny
    
    Allow from all
    
    Require all granted
    
    AllowOverride All #this allows .htaccess
    
>>>>>>> refs/remotes/origin/master
  </Directory>
