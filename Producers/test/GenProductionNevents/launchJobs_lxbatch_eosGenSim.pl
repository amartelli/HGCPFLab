
#!/usr/bin/perl

# ----------------------------------------------------------------------------
#      MAIN PROGRAM
# ----------------------------------------------------------------------------

use Env;

#PG lettura dei parametri da cfg file
#PG --------------------------------
print "reading ".$ARGV[0]."\n" ;

open (USERCONFIG,$ARGV[0]) ;

while (<USERCONFIG>)
{
    chomp; 
    s/#.*//;                # no comments
    s/^\s+//;               # no leading white
    s/\s+$//;               # no trailing white
#    next unless length;     # anything left?
    my ($var, $value) = split(/\s*=\s*/, $_, 2);
    $User_Preferences{$var} = $value;
}

$BASEDir          = $User_Preferences{"BASEDir"};
$FILEName         = $User_Preferences{"FileName"} ;
$EXEName          = $User_Preferences{"EXEName"} ;
$JOBCfgTemplate   = $User_Preferences{"JOBCfgTemplate"} ;
$OUTPUTSAVEPath   = $User_Preferences{"OUTPUTSAVEPath"} ;
$OUTPUTFILEName   = $User_Preferences{"OUTPUTFILEName"} ;
$JOBModulo        = $User_Preferences{"JOBModulo"} ;
$JOBNumber        = $User_Preferences{"JOBNumber"} ;


print "BASEDir = "          .$BASEDir."\n" ;
print "FileName = "         .$FileName."\n" ;
print "EXEName = "          .$EXEName."\n" ;
print "JOBCfgTemplate = "   .$JOBCfgTemplate."\n" ;
print "OUTPUTSAVEPath = "   .$OUTPUTSAVEPath."\n" ;
print "OUTPUTFILEName = "   .$OUTPUTFILEName."\n" ;
print "JOBModulo = "        .$JOBModulo."\n\n" ;
print "JOBNumber = "        .$JOBNumber."\n\n" ;


$sampleJobListFile = "./lancia.sh";
open(SAMPLEJOBLISTFILE, ">", $sampleJobListFile);

    
    print "NumberOfJobs = ".$JOBNumber."\n";
    
    
    ################
    # loop over jobs 
    ################
    
    for($jobIt = 1; $jobIt <= $JOBNumber; ++$jobIt)
    { 
	print "jobIt = ".$jobIt."\n";
	$currDir = `pwd` ;
	chomp ($currDir) ;
    
	$jobDir = $currDir."/JOB_".$jobIt ;
	system ("mkdir ".$jobDir." \n") ;
    
	$tempBjob = $jobDir."/bjob_".$jobIt.".sh" ;
	$command = "touch ".$tempBjob ;
	system ($command) ;
	$command = "chmod 777 ".$tempBjob ;
	system ($command) ;
    


    
    
	$tempo1 = "./tempo1" ;
	$OUTPUTFILENameOK = $OUTPUTFILEName."_".$jobIt.".root";
	print "OUTPUTFILENameOK = ".$OUTPUTFILENameOK."\n";
	system ("cat ".$JOBCfgTemplate."   | sed -e s%OUTPUTFILENAME%".$OUTPUTFILENameOK.
		"%g > ".$tempo1) ;
    
	$tempo2 = "./tempo2" ;
	$jobItEvt = ( ($jobIt -1 ) * 200) + 1; 
	print "firstEvent = ".$jobItEvt."\n";
	system ("cat ".$tempo1."   | sed -e s%FIRSTEVENT%".$jobItEvt.
		                    "%g > ".$tempo2) ;
    
    
	$JOBCfgFile = $jobDir."/".$EXEName."_".$jobIt.".py" ;
	system ("mv ".$tempo2." ".$JOBCfgFile) ;
	system ("rm ./tempo*") ;
    
    
    
    
    
    
    ######################
    # make job files
    ######################    
    
	open (SAMPLEJOBFILE, ">", $tempBjob) or die "Can't open file ".$tempBjob;

	$command = "#!/bin/bash" ;
	print SAMPLEJOBFILE $command."\n";

	$command = "cd ".$BASEDir ;
	print SAMPLEJOBFILE $command."\n";

	$command = "export SCRAM_ARCH=slc6_amd64_gcc472" ;
	print SAMPLEJOBFILE $command."\n";
    
	$command = "eval `scramv1 ru -sh`" ;
	print SAMPLEJOBFILE $command."\n";
    
	$command = "cd -" ;
	print SAMPLEJOBFILE $command."\n";


	$command = "cmsMkdir ".$OUTPUTSAVEPath;
	print SAMPLEJOBFILE $command."\n";

	$command = "cmsRun ".$JOBCfgFile ;
	print SAMPLEJOBFILE $command."\n";

	$command = "cmsStage ".$OUTPUTFILEName."_".$jobIt.".root ".$OUTPUTSAVEPath;
	print SAMPLEJOBFILE $command."\n";

	
	############
	# submit job
	############
	
	$command = "bsub -cwd ".$jobDir." -q cmscaf1nd ".$tempBjob."\n" ;  
	print SAMPLEJOBLISTFILE $command."\n";
    }
    
