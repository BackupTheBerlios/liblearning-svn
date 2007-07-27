#!/usr/bin/perl -w

my $title = "";

while (<STDIN>) {
	s/\$\$TITLE\$\$/$title/g;

	if (/\@title (.*)/) {
		$title = $1;
	} elsif (/\@see (.*)/) {
		my @a = split(/,/, $1);
		print "<p><b>See also</b>&nbsp;&nbsp;&nbsp;";
		for my $i (@a) {
			$i =~ s/^\s*//g;
			$i =~ s/\s*$//g;
			print "<a href=\"$i.html\">$i</a>&nbsp;&nbsp;&nbsp;\n";
		}
		print "</p>\n";
	} elsif (/\@file ([^\s]+)/) {
		open (F, $1) or die ("could not open file $1\n");
		while (<F>) {
			s/</&lt;/g;
			s/>/&gt;/g;
			print;
		}
	} else {
		print;
	}
}
