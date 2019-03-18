use strict;
use warnings;
use diagnostics;

sub report_error {
	my ($error_message_string) = @_;
	# print STDERR "$error_message_string\n"; Commented out because it's redundant. 

	my $date_string = localtime();
	print STDOUT "Error message: $error_message_string\nOccured at $date_string.";
}

# Testing subroutine "report_erorr"
my $file_name = "some_non_existent_file";

open (my $f, $file_name) || report_error ("Failed to open $file_name");

# Output was...
# Error message: Failed to open some_non_existent_file
# Occured at Sun Jul  9 21:42:31 2017.