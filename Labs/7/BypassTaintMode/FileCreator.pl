#!/usr/bin/perl -T

print "Give a Name to a New File:\n";
$filename=<STDIN>;

if ($filename =~ /(^(\w)+\.(\w)+$)/) {
    $filename = $1;
    open(FOO, "> $filename");
    print "File Created!\n";
} else {
    print "File Not Created!\n";
}

