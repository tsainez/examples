<?php

	$string1 = "abc and the rest is left out";
	$string2 = "Once upon a time abcdefg";
	$string3 = "Hello world from php abc";

	class regex_lab { 
		public function findABC($string) {
			# return true if substring "abc" is found 
			# use preg_match

			$regex = "/abc/";
			
			if(preg_match($regex, $string, $match)) {
				echo "true "; 
				# for some reason, writing 'return true;' doesn't work.
			} else {
				echo "false ";
			}
		}

		public function firstFindABC($string) {
			# return true if substring "abc" is found at the beginning
			# use preg_match 

			$regex = "/^abc.*/";

			if(preg_match($regex, $string, $match)) {
				echo "true ";
				# for some reason, writing 'return true;' doesn't work.
			} else {
				echo "false ";
			}
		}

		public function lastFindABC($string) {
			# return true if substring "abc" is found at the end
			# use preg_match()

			$regex = "/.abc$/";

			if(preg_match($regex, $string, $match)) {
				echo "true ";
				# for some reason, writing 'return true;' doesn't work.
			} else {
				echo "false ";
			}
		}

		public function appendNewLine($string) {
			# put a <br> tag at the beginning of string parameter
			# use preg_replace()

			$regex = "/^/";

			$newString = preg_replace($regex, "<br>", $string);
			echo $newString;
		}

		public function removeNewLine($string) {
			# get rid of any newline characters 
			# use preg_replace() 

			$regex = "/<br>/";
			$newString = preg_replace($regex, "", $string);
			echo $newString;
		}
	}	

	# Test Case

	$testLab = new regex_lab;
	echo "Created new regex_lab";

	echo "<br>Testing findABC() function: ";
	echo $testLab->findABC($string1);
	echo $testLab->findABC($string2);
	echo $testLab->findABC($string3);

	echo "<br>Testing firstFindABC() function: ";
	echo $testLab->firstFindABC($string1);
	echo $testLab->firstFindABC($string2);
	echo $testLab->firstFindABC($string3);

	echo "<br>Testing lastFindABC() function: ";
	echo $testLab->lastFindABC($string1);	
	echo $testLab->lastFindABC($string2);
	echo $testLab->lastFindABC($string3);

	echo "<br>Appending new line to every string.";
	$testLab->appendNewLine($string1);
	$testLab->appendNewLine($string2);
	$testLab->appendNewLine($string3);

	echo "<br>Removing new line to every string:";
	$testLab->removeNewLine($string1);
	$testLab->removeNewLine($string2);
	$testLab->removeNewLine($string3);

	echo "<br>End of lab.";
?>