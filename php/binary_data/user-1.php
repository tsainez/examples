<?php
class users extends database {
	public $fname;
	public $lname;
	public $profilePic;
	public $email;
	public $password;
	public $userid;

	public function saveUserDatav2() {
		parent::connect_to_database("localhost", "barreto", "sTovok0r", "movieCollection");
		$queryStr = "INSERT INTO `users` (`userID`, `fname`, `lname`, `pic`) VALUES (NULL, ?, ?, ?)";
		$params = [$this->fname, $this->lname, $this->profilePic];
		$result = parent::executeQuery($queryStr, $params);

		if ($result === TRUE) {
			$uid = parent::returnLastRecordID();
			$success = $uid;
		} else {
			$success = FALSE;
		}

		parent::disconnect_from_database();
		return $success;
	}

	public function getRecordById($myid) {
		parent::connect_to_database("localhost", "barreto", "sTovok0r", "movieCollection");
		$queryStr = "SELECT * FROM `users` WHERE `userID` = ?";
		$params = [$myid];
		parent::executeQuery($queryStr, $params);
		$profileInfo = parent::getResultSet();
		$this->userid = $profileInfo['userID'];
		$this->fname = $profileInfo['fname'];
		$this->lname = $profileInfo['lname'];
		$this->profilePic = $profileInfo['pic'];
		$this->email = $profileInfo['email'];
		$this->password = crypt($profileInfo['password'],"sdjeyrfgdb4334");
		parent::disconnect_from_database();
	}

	// Getter methods from the users class

public function getfName() {
	return $this->fname;
}

public function getlName() {
	return $this->lname;
}

public function getProfilePic() {
	return $this->profilePic;
}

public function getEmail() {
	return $this->email;
}

	public function getPassword() {
		return $this->password;
	}
}
?>