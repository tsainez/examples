use strict;
use warnings;
use diagnostics;

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