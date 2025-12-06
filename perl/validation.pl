#
#  validation.pl
#
#  Created by Anthony Sainez on 9 July 2017
#  Copyright © 2020 Anthony Sainez. All rights reserved.
#

use strict;
use warnings;
use diagnostics;

=head1 NAME

validation.pl - String validation and transformation utilities.

=head1 DESCRIPTION

This script provides subroutines to validate alphanumeric characters and
transform animal names in a sentence according to specific rules.

=cut

=head2 validate_alphanumeric

    validate_alphanumeric($string)

Iterates through each character of the input string and prints it if it is alphanumeric.

=over 4

=item * C<$string> - The input string to validate.

=back

=cut
sub validate_alphanumeric {
	my ($string) = @_;
	my @chars = split("", $string); # tokenize into individual characters, catching all

	foreach my $char (@chars) {
		if ($char =~ /[[:alnum:]]/) {
			# Works as intended. My compiler refuses to accept POSIX it's double bracketed.
			print "$char\n";
		}
	}
}

validate_alphanumeric("This is alphanumeric. This is not: !@#");

=head2 search_for_animal

    search_for_animal($string)

Transforms animal names in the input string based on a cyclic rule:
dog -> cat, cat -> mouse, mouse -> dog.
Also handles plural forms: dogs -> cats, cats -> mice.

=over 4

=item * C<$string> - The input sentence containing animal names.

=back

=cut
sub search_for_animal {
	# RULES:
	# dog to cat
	# cat to mouse
	# mouse to dog

	my ($string) = @_;
	my @words = split(" ", $string); # tokenize into words, using space as seperator

	foreach my $word (@words) {
		# Since PERL does not include a switch statement without having to
		# have dependencies, we'll be using an ugly if else chain.

		if ($word =~ /dogs/) { # dog case, change to cat.
			$word = "cats";
		} elsif ($word =~ /cats/) { # cat case, change to mouse.
			$word = "mice";

			# We want to check plural, since if it doesn't catch it if it's plural,
			# then it must be singular. If it's caught when it's singular, theres
			# still one character left to check before we decide it's plural, but
			# you would skip over it.

		} elsif ($word =~ /cat/) { # cats case, change to mice.
			$word = "mouse";
		}elsif ($word =~ /mouse/) { # mouse case, change to dog.
			$word = "dog";
		} else {
			# since it's none of the required words, we'll increment to the next one.
		}

		# Let's print out the word we're on with a space infront of it to make a sentence.
		print "$word ";
	} # end foreach
}

search_for_animal("Do dogs eat cats, or does your cat eat a mouse.");
