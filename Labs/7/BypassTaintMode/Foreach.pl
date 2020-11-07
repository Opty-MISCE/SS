#!/usr/bin/perl -T

print "Give a Name to a New File:\n";
$filename=<STDIN>;
$fn = "";

foreach $c (split('', $filename)) {
    
    if ($c eq 'A') {
        $fn .= 'A';
    } elsif ($c eq 'B') {
        $fn .= 'B';
    } elsif ($c eq 'C') {
        $fn .= 'C';
    } elsif ($c eq '1') {
        $fn .= '1';
    } elsif ($c eq '2') {
        $fn .= '2';
    } elsif ($c eq '3') {
        $fn .= '3';
    }
}

open(FOO, "> $fn");
print "File '$fn' Created!\n";
