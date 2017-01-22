@letters=(a..z);
$total=@letters;
open(FILE, '>', $ARGV[1]) or die "Could not open file.";
for(1 .. $ARGV[0]) {
	print FILE $letters[rand $total];
}
close FILE;