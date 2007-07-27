#!/usr/bin/perl -w

my $x = "";

my $comment = 0;
my $in_descr = 0;
my $in_example = 0;
my $in_example_descr = 0;
my $in_mem = 0;
my $in_note = 0;
my $chk = 0;
my $get_sig = 0;

my $members = "";
my $sig = "";
my $class = "";
my $descr = "";
my $example = "";
my $example_descr = "";
my $header = trim($ARGV[0]);
my $tmpl = "";
my $tmpl_sig = "";
my $mem = "";
my $see = "";
my $note = "";
my $notes = 0;

my $dstdir = $ARGV[2];

open(F, $ARGV[0]) or die("could not open file");
open(G, $ARGV[1]) or die("could not open template");

while (<G>) {
	$x .= $_;
}

sub getline {
	my $l = <F>;
	$l;
}

while (<F>) {
	chomp;
	my $l = $_;
	while (($l =~ /\\$/) && ($_ = getline())) {
		chomp;
		$l =~ s/\\$/ /g;
		$l .= $_;
	}
	parse_line($l."\n");
}

sub reset_in {
	if ($in_note) {
		$note .= "</p>\n";
	}
	$in_descr = 0;
	$in_example = 0;
	$in_example_descr = 0;
	$in_mem = 0;
	$in_note = 0;
}

sub parse_line {
	$_ = shift;
	if (/\/\*/) {
		$comment = 1;
		$chk = 0;
	}
	if ($comment == 1) {
		if (/\@class (.*)/s) {
			$class = $1;
			$class =~ s/\s*\*\/\s*//;
		} elsif (/\@see (.*)/s) {
			reset_in();
			my $s = $1;
			$s =~ s/\s*$//;
			$s =~ s/^\s*//;
			if (length($see) > 0) {
				$see .= ", ";
			}
			$see .= "<a href=\"$s.html\">$s</a>";
		} elsif (/\@1(.*)/) {
			my $x = $1;
			if ($x =~ /(.*?)\@2(.*?)\@3(.*)/) {
				$tmpl .= "<tr><td valign=top><tt>".enc($1).
					"</tt></td><td valign=top>".enc($2).
					"</td><td valign=top><tt>".enc($3).
					"</tt></td></tr>\n";
			}
		} elsif (/\@description(.*)/) {
			reset_in();
			$in_descr = 1;
			$descr = add_data($descr, $1);
		} elsif (/\@example(.*)/) {
			reset_in();
			$in_example = 1;
			$example = add_data($example, $1);
		} elsif (/\@exdescription(.*)/) {
			reset_in();
			$in_example_descr = 1;
			$example_descr = add_data($example_descr, $1);
		} elsif (/\@mem(.*)/) {
			reset_in();
			$in_mem = 1;
			$sig = "";
			$mem = "";
			$mem = add_data($mem, $1);
		} elsif (/\@note(.*)/) {
			reset_in();
			$in_note = 1;
			$notes++;
			$note = "<p><a name=\"note$notes\">[$notes] ".add_data($note, $1);
			$mem .= " [<a href=\"#note$notes\">".$notes."</a>]";
		} elsif ($in_note == 1) {
			$note = add_data($note, $_);
		} elsif ($in_descr == 1) {
			$descr = add_data($descr, $_);
		} elsif ($in_example == 1) {
			$example = add_data($example, $_);
		} elsif ($in_example_descr == 1) {
			$example_descr = add_data($example_descr, $_);
		} elsif ($in_mem == 1) {
			$mem = add_data($mem, $_);
		}
	}
	if ($comment == 0 && $get_sig == 1) {
		$sig .= $_;
		if ($_ =~ /[\{;]/) {
			if ($sig =~ /typedef.*?\s([a-zA-Z_]+)\s*;/) {
				$members .= "<tr><td valign=top><tt>".$1."</tt></td><td valign=top>$mem</td></tr>";
			} elsif ($sig =~ /typedef/) {
				# XXX retrieve lines until ; has been read
				$sig .= getline();
				if ($sig =~ /typedef.*?\s([a-zA-Z_]+)\s*;/s) {
					$members .= "<tr><td valign=top><tt>".$1."</tt></td><td valign=top>$mem</td></tr>";
				}
			} elsif ($sig =~ /template/) {
				if ($sig =~ /(template.*?>)\s+([^>]+)\s*\((.*?)\)(.*?)\{/s) { # template constructor
					# template<...> constructor_name(...)
					# $1 = template<...>, $2 = constructor name, $3 = signature
					$members .= "<tr><td valign=top><tt>".enc($1)."<br>$2($3)</tt></td><td valign=top>$mem</td></tr>";
				} elsif ($sig =~ /(template.*?>)\s+([^>]+)\s+([^\s]+)\s*\((.*?)\)(.*?)\{/s) { # method
					# template<...> return_type method_name(...)
					# $1 = template<...>, $2 = return_type, $3 = method_name, $4 = signature
					$members .= "<tr><td valign=top><tt>".enc($1)."<br>$2 $3($4)</tt></td><td valign=top>$mem</td></tr>";
				}
			} else {
				if ($sig =~ /([a-zA-Z_]+)\s*\((.*?)\)(.*?)\{/s) { # constructor without template
					$members .= "<tr><td valign=top><tt>".enc($1)."($2)</tt></td><td valign=top>$mem</td></tr>";
				} elsif ($sig =~ /([a-zA-Z_&]+)\s+([^\s]+)[+\s]*\((.*?)\)(.*?)\{/s) { # method
					# return_type method_name(...)
					# $1 = return_type, $2 = method_name, $3 = signature
					my $rt = $1;
					my $mn = $2;
					my $si = $3;
					if ($sig =~ /\)\s*const/s) {
						$members .= "<tr><td valign=top><tt>".enc($rt)." $mn($si) const</tt></td><td valign=top>$mem</td></tr>";
					} else {
						$members .= "<tr><td valign=top><tt>".enc($rt)." $mn($si)</tt></td><td valign=top>$mem</td></tr>";
					}
				}
			}
			$get_sig = 0;
		}
	}
	if (/\*\//) {
		if ($in_mem || $in_note) {
			$get_sig = 1;
		}
		reset_in();
		$comment = 0;
		if (length($tmpl_sig) == 0) {
			$chk = 1;
		}
	} elsif ($chk == 1 && length($class) > 0) {
		if (/class/) {
			$chk = 0;
            $tmpl_sig .= " ";
		} else {
			$tmpl_sig .= $_;
		}
	}
}

if (length($class) == 0) {
	exit(0);
}

$class = enc($class);
$header = enc($header);
$example = enc($example);

my $plainheader = $header;
$plainheader =~ s/.*\///;
my $def = "Defined in header <a href=\"$plainheader\">$header</a>";
#print $class."\n";
#print $descr."\n";
#print $example."\n";
#print $header."\n";
#print $tmpl."\n";

$tmpl_sig =~ s/^\s//g;
$tmpl_sig =~ s/\s*=.*?,/,/g;
$tmpl_sig =~ s/\s*=.*?>$/>/g;
$tmpl_sig =~ s/^template//g;
$tmpl_sig =~ s/typename\s*//g;
$tmpl_sig = enc($tmpl_sig);

$x =~ s/\$\$CLASSNAME\$\$/$class$tmpl_sig/;
$x =~ s/\$\$DESCRIPTION\$\$/$descr/;
$x =~ s/\$\$EXAMPLE\$\$/$example/;
$x =~ s/\$\$DEFINITION\$\$/$def/;
$x =~ s/\$\$TEMPLATES\$\$/$tmpl/;
$x =~ s/\$\$EXAMPLEDESCRIPTION\$\$/$example_descr/;
$x =~ s/\$\$MEMBERS\$\$/$members/;
$x =~ s/\$\$SEE\$\$/$see/;
$x =~ s/\$\$NOTES\$\$/$note/;

my $dst = $dstdir."/".$class.".html";
open(H, ">".$dst) or die("could not open file ".$dst);
print H $x;
close(H);



sub add_data {
	my $data = shift;
	my $add = shift;
	if ($add =~ /(.*?)\*\//) {
		$add = $1;
	}
	$data .= $add;
	$data;
}

sub trim {
	my $d = shift;
	if ($d =~ /^[\s\.\/]+(.*)/) {
		$d = $1;
	}
	$1;
}

sub enc {
	my $d = shift;
	$d =~ s/</&lt;/g;
	$d =~ s/>/&gt;/g;
	$d =~ s/^\s//;
	$d =~ s/\s$//;
	if (length($d) == 0) {
		$d = "&nbsp;";
	}
	$d;
}

