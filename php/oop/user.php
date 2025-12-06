<?php

	include('database.php');

	$data = new database; # is this necessary?

	/**
	 * Represents a user in the system.
	 *
	 * Extends the database class to provide functionality for setting user details
	 * and saving them to the database.
	 */
	class user extends database {
		# i like to divide my classes into two sections,
		# that is, data and functions. See below.

		# data declaraction section
		/** @var string The user's first name. */
		private $firstName;
		/** @var string The user's last name. */
		private $lastName;
		/** @var string The user's email address. */
		private $email;
		# private $userid;
		# no need for userid

		# function declaration section
		/**
		 * Sets the user's first name.
		 *
		 * @param string $newName The new first name (max 50 chars).
		 */
		public function set_UserFirstName($newName) {
			# varchar(50)
			$this->firstName = $newName;
		}

		/**
		 * Sets the user's last name.
		 *
		 * @param string $newName The new last name (max 50 chars).
		 */
		public function set_UserLastName($newName) {
			# varchar(50)
			$this->lastName = $newName;
		}

		/**
		 * Sets the user's email address.
		 *
		 * @param string $newEmail The new email address (max 100 chars).
		 */
		public function set_UserEmail($newEmail) {
			# varchar(100)
			$this->email = $newEmail;
		}

		/**
		 * Saves the user to the database.
		 *
		 * Connects to the database and executes an INSERT query.
		 * Warning: This method is vulnerable to SQL injection.
		 */
		public function save_User() {
			$this->connect_to_database();

			# not bullet-proof
			$this->run_query("INSERT INTO users (fname, lname, email) VALUES ('".$this->firstName."', '".$this->lastName"', '".$this->email."')");
		}
	}

?>