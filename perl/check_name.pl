#!/usr/bin/env perl

use strict;
use warnings;
use utf8;

use Data::Dumper;
use Getopt::Long;
use File::Find;
use File::stat;
use Image::EXIF;
use Image::ExifTool;
use Time::Piece;
use Time::Seconds;

my %OPTS = ('fast' => 0, 'verbose' => 0, 'debug' => 0);
my $PATH = '.';

GetOptions(\%OPTS, 'fast', 'verbose', 'debug') or die;
$PATH = $ARGV[0] if $#ARGV >= 0;

my $TOTAL_JPG = 0;
my $TOTAL_MP4 = 0;
my $TOTAL = 0;

if (not $OPTS{debug}) {
    # suppress error message from Image::EXIF
    open STDERR, ">>/dev/null";
}

sub to_time($) {
    my ($str) = @_;
    return Time::Piece->strptime($str, '%Y:%m:%d %H:%M:%S');
}

sub get_exif_with_exif($) {
    my ($f) = @_;
    my $exif = Image::EXIF->new($f);
    my $info = $exif->get_all_info();
    my %r;
    my $time_str = $info->{other}{'Image Generated'};
    if ($time_str) {
        $r{'time'} = to_time($time_str);
    }
    my $camera_str = $info->{camera}{'Camera Model'};
    if ($camera_str) {
        $r{'camera'} = $camera_str;
    }
    if ($OPTS{debug}) {
        $r{debug} = Dumper $info;
    }
    return \%r;
}

# Image::ExifTool is slower than Image::EXIF
sub get_exif_with_exiftool($) {
    my ($f) = @_;
    my $info = Image::ExifTool::ImageInfo($f);
    my %r;
    my $time_str = $info->{'DateTimeOriginal'};
    if ($time_str) {
        $r{time} = to_time($time_str);
    }
    my $camera_str = $info->{'Model'};
    if ($camera_str) {
        $r{camera} = $camera_str;
    }
    my $keywords = $info->{'Keywords'};
    if ($keywords) {
        $r{keywords} = $keywords;
    }
    if ($OPTS{debug}) {
        $r{debug} = Dumper $info,
    }
    return \%r;
}

sub get_dir_info($) {
    my ($dir) = @_;
    my %r;
    if ($dir =~ /(?:\/|^)(\d{4})(\d{2})$/) {
        $r{year} = $1;
        $r{month} = $2;
    } elsif ($dir =~ /(?:\/|^)(\d{4})$/) {
        $r{year} = $1;
    }
    return \%r;
}

sub check_path() {
    return if substr($_, 0, 1) eq '.';
    my $dir = $File::Find::dir;
    my %checks = (
        Type => 'X',
        EXIF => 'X',
        Name => 'X',
        InDir => 'X',
    );
    if (-f) {
        my $time;
        if (/\.mp4$/) {
            $TOTAL_MP4++;
            $checks{Type} = 'V';
            $checks{EXIF} = '-';
            if (/^\d{6}_\d{6}_/) {
                $checks{Name} = 'O';
                $time = Time::Piece->strptime(substr($_, 0, 13), '%y%m%d_%H%M%S');
            }
        } elsif (/\.jpg$/) {
            $TOTAL_JPG++;
            $checks{Type} = 'P';
            my $info;
            if ($OPTS{'fast'}) {
                $info = get_exif_with_exif($_);
            } else {
                $info = get_exif_with_exiftool($_);
            }
            if ($OPTS{'debug'}) {
                print $info->{debug};
            }
            $time = $info->{time};
            if ($time) {
                my $time_str = $time->strftime("%y%m%d_%H%M%S");
                my $camera = $info->{camera};
                if ($camera) {
                    $camera =~ tr/ ,/_/;
                    $camera = '_'.$camera;
                } else {
                    $camera = '';
                }
                $checks{EXIF} = 'O';
                if ($OPTS{fast}) {
                    if (/^\Q$time_str\E_.+\Q$camera\E(?:-\d{3})?\.jpg$/) {
                        $checks{Name} = 'O';
                    }
                } else {
                    my $keywords = $info->{keywords};
                    $keywords =~ s/,\s*/_/g;
                    if (/^\Q$time_str\E_\Q$keywords$camera\E(?:-\d{3})?\.jpg$/) {
                        $checks{Name} = 'O';
                    }
                }
            }
        }
        if ($time) {
            my $dir_info = get_dir_info($dir);
            if ($dir_info->{year} == $time->year and $dir_info->{month} == $time->mon) {
                $checks{InDir} = 'O';
            }
        }
    } elsif (-d) {
        $checks{EXIF} = '-';
        my $info = get_dir_info($_);
        if ($info->{month}) {
            $checks{Type} = 'M';
            $checks{Name} = 'O';
            my $dir_info = get_dir_info($dir);
            if ($dir_info->{year} and !$dir_info->{month} and $info->{year} eq $dir_info->{year}) {
                $checks{InDir} = 'O';
            }
        } elsif ($info->{year}) {
            $checks{Type} = 'Y';
            $checks{Name} = 'O';
            $checks{InDir} = '-';
        }
    }
    my $error = 0;
    my $msg = "Check(".sprintf("%6d", $TOTAL++)."): ";
    for my $k (sort keys %checks) {
        my $v = $checks{$k};
        if ($v eq 'X') {
            $error = 1;
        }
        $msg .= "$k($v), ";
    }
    $msg .= "Dir($dir), File($_).\n";
    print $msg if $error or $OPTS{verbose};
}

print "Recursively search path \"$PATH\"...\n";

find(\&check_path, $PATH);

print "$TOTAL_JPG photoes and $TOTAL_MP4 videos are checked.\n";
