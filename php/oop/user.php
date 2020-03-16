<?php

	include('database.php');

	$data = new database; # is this necessary?

	class user extends database {
		# i like to divide my classes into two sections,
		# that is, data and functions. See below.

		# data declaraction section
		private $firstName;
		private $lastName;
		private $email;
		# private $userid;
		# no need for userid

		# function declaration section
		public function set_UserFirstName($newName) {
			# varchar(50)
			$this->firstName = $newName;
		}

		public function set_UserLastName($newName) {
			# varchar(50)
			$this->lastName = $newName;
		}

		public function set_UserEmail($newEmail) {
			# varchar(100)
			$this->email = $newEmail;
		}

		public function save_User() {
			$this->connect_to_database();

			# not bullet-proof
			$this->run_query("INSERT INTO users (fname, lname, email) VALUES ('".$this->firstName."', '".$this->lastName"', '".$this->email."')");
		}
	}

?>