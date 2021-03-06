#include "garlic-cli.h"
#include <iostream>

const string VERSION = "1.0.1";

const string ARG_OVERLAP_FRAC = "--overlap-frac";
const double DEFAULT_OVERLAP_FRAC = 0.25;
const string HELP_OVERLAP_FRAC = "The minimum fraction of overlapping windows above the LOD cutoff required\n\
\tto begin constructing a run.";

const string ARG_OUTFILE = "--out";
const string DEFAULT_OUTFILE = "outfile";
const string HELP_OUTFILE = "The base name for all output files.";

/*
const string ARG_THREADS = "--threads";
const int DEFAULT_THREADS = 1;
const string HELP_THREADS = "The number of threads to spawn during calculations.";
*/

const string ARG_ERROR = "--error";
const double DEFAULT_ERROR = -1;
const string HELP_ERROR = "The assumed genotyping error rate.";

const string ARG_WINSIZE = "--winsize";
const int DEFAULT_WINSIZE = 10;
const string HELP_WINSIZE = "The window size in # of SNPs in which to calculate LOD scores.";

const string ARG_WINSIZE_MULTI = "--winsize-multi";
const int DEFAULT_WINSIZE_MULTI = -1;
const string HELP_WINSIZE_MULTI = "Provide several window sizes (in # of SNPs) to calculate LOD scores.\n\
\tLOD score KDEs for each window size will be output for inspection.";

const string ARG_AUTO_WINSIZE = "--auto-winsize";
const bool DEFAULT_AUTO_WINSIZE = false;
const string HELP_AUTO_WINSIZE = "Initiates an ad hoc method for automatically selecting the # of SNPs in which to\n\
\tcalculate LOD scores. Starts at the value specified by --winsize and increases\n\
\tby <step size> SNPs until finished.";

const string ARG_AUTO_WINSIZE_STEP = "--auto-winsize-step";
const int DEFAULT_AUTO_WINSIZE_STEP = 10;
const string HELP_AUTO_WINSIZE_STEP = "Step size for automatic window selection algorithm.";

const string ARG_MAX_GAP = "--max-gap";
const int DEFAULT_MAX_GAP = 200000;
const string HELP_MAX_GAP = "A LOD score window is not calculated if the gap (in bps)\n\
\tbetween two loci is greater than this value.";

const string ARG_RESAMPLE = "--resample";
const int DEFAULT_RESAMPLE = 0;
const string HELP_RESAMPLE = "Number of resamples for estimating allele frequencies.\n\
\tWhen set to 0 (default), garlic will use allele\n\
\tfrequencies as calculated from the data.";

const string ARG_TPED = "--tped";
const string DEFAULT_TPED = "none";
const string HELP_TPED = "A tped formatted file containing map and genotype information.";

const string ARG_TFAM = "--tfam";
const string DEFAULT_TFAM = "none";
const string HELP_TFAM = "A tfam formatted file containing population and individual IDs.";

const string ARG_RAW_LOD = "--raw-lod";
const bool DEFAULT_RAW_LOD = false;
const string HELP_RAW_LOD = "If set, LOD scores will be output to gzip compressed files.";

const string ARG_LOD_CUTOFF = "--lod-cutoff";
const double DEFAULT_LOD_CUTOFF = -999999;
const string HELP_LOD_CUTOFF = "For LOD based ROH calling, specify a single LOD score cutoff\n\
\tabove which ROH are called in all populations.  By default, this is chosen\n\
\tautomatically with KDE.";

const string ARG_BOUND_SIZE = "--size-bounds";
const double DEFAULT_BOUND_SIZE = -1;
const string HELP_BOUND_SIZE = "Specify the short/medium and medium/long\n\
\tROH boundaries.  By default, this is chosen automatically\n\
\twith a 3-component GMM.  Must provide 2 numbers.";

const string ARG_TPED_MISSING = "--tped-missing";
const char DEFAULT_TPED_MISSING = '0';
const string HELP_TPED_MISSING = "Single character missing data code for TPED files.";

const string ARG_FREQ_FILE = "--freq-file";
const string DEFAULT_FREQ_FILE = "none";
const string HELP_FREQ_FILE = "A file specifying allele frequencies for\n\
\teach population for all variants. File format:\n\
\tSNP\tALLELE\t<pop1 ID> <pop2 ID> ...\n\
\t<locus ID> <allele> <pop1 freq> <pop2 freq> ...\n\
\tBy default, this is calculated automatically\n\
\tfrom the provided data.";

const string ARG_FREQ_ONLY = "--freq-only";
const bool DEFAULT_FREQ_ONLY = false;
const string HELP_FREQ_ONLY = "If set, calculates a freq file from provided data and then exits.";

const string ARG_KDE_SUBSAMPLE = "--kde-subsample";
const int DEFAULT_KDE_SUBSAMPLE = 10;
const string HELP_KDE_SUBSAMPLE = "The number of individuals to randomly sample for LOD score KDE. If there\n\
\tare fewer individuals in the population all are used.\n\
Set <= 0 to use all individuals (may use large amounts of RAM).";

const string ARG_BUILD = "--build";
const string DEFAULT_BUILD = "none";
const string HELP_BUILD = "Choose which genome build to use for centromere locations (hg18, hg19, or hg38).\n";

const string ARG_CENTROMERE_FILE = "--centromere";
const string DEFAULT_CENTROMERE_FILE = "none";
const string HELP_CENTROMERE_FILE = "Provide custom centromere boundaries. Format <chr> <start> <end>.\n";
/*
const string ARG_FEATURE_TPED = "--tped-counting";
const string DEFAULT_FEATURE_TPED = "_none";
const string HELP_FEATURE_TPED = "A TPED formatted file containing genotypes that are classified in the feature file.\n\
Sites not in the feature file are ignored.";

const string ARG_FEATURE_TFAM = "--tfam-counting";
const string DEFAULT_FEATURE_TFAM = "_none";
const string HELP_FEATURE_TFAM = "A TFAM formatted file containing individuals listed in the corresponding TPED file.\n\
Individuals without ROH calls are ignored.";

const string ARG_FEATURES = "--features";
const string DEFAULT_FEATURES = "_none";
const string HELP_FEATURES = "A feature file giving classifications";
*/

param_t *getCLI(int argc, char *argv[])
{
	param_t *params = new param_t;
	params->addFlag(ARG_OVERLAP_FRAC, DEFAULT_OVERLAP_FRAC, "", HELP_OVERLAP_FRAC);
	params->addFlag(ARG_OUTFILE, DEFAULT_OUTFILE, "", HELP_OUTFILE);
	//params->addFlag(ARG_THREADS, DEFAULT_THREADS, "", HELP_THREADS);
	params->addFlag(ARG_ERROR, DEFAULT_ERROR, "", HELP_ERROR);
	params->addFlag(ARG_WINSIZE, DEFAULT_WINSIZE, "", HELP_WINSIZE);
	//params->addFlag(ARG_POINTS, DEFAULT_POINTS, "", HELP_POINTS);
	//params->addFlag(ARG_BW, DEFAULT_BW, "", HELP_BW);
	params->addFlag(ARG_MAX_GAP, DEFAULT_MAX_GAP, "", HELP_MAX_GAP);
	params->addFlag(ARG_RESAMPLE, DEFAULT_RESAMPLE, "", HELP_RESAMPLE);
	params->addFlag(ARG_TPED, DEFAULT_TPED, "", HELP_TPED);
	params->addFlag(ARG_TFAM, DEFAULT_TFAM, "", HELP_TFAM);
	params->addFlag(ARG_RAW_LOD, DEFAULT_RAW_LOD, "", HELP_RAW_LOD);
	params->addListFlag(ARG_BOUND_SIZE, DEFAULT_BOUND_SIZE, "", HELP_BOUND_SIZE);
	params->addFlag(ARG_LOD_CUTOFF, DEFAULT_LOD_CUTOFF, "", HELP_LOD_CUTOFF);
	//params->addFlag(ARG_LOD_CUTOFF_FILE, DEFAULT_LOD_CUTOFF_FILE, "", HELP_LOD_CUTOFF_FILE);
	//params->addFlag(ARG_BOUND_SIZE_FILE, DEFAULT_BOUND_SIZE_FILE, "", HELP_BOUND_SIZE_FILE);
	params->addFlag(ARG_TPED_MISSING, DEFAULT_TPED_MISSING, "", HELP_TPED_MISSING);
	params->addFlag(ARG_FREQ_FILE, DEFAULT_FREQ_FILE, "", HELP_FREQ_FILE);
	params->addFlag(ARG_FREQ_ONLY, DEFAULT_FREQ_ONLY, "", HELP_FREQ_ONLY);
	params->addListFlag(ARG_WINSIZE_MULTI, DEFAULT_WINSIZE_MULTI, "", HELP_WINSIZE_MULTI);
	//params->addFlag(ARG_POP_SPLIT, DEFAULT_POP_SPLIT , "", HELP_POP_SPLIT);
	params->addFlag(ARG_KDE_SUBSAMPLE, DEFAULT_KDE_SUBSAMPLE , "", HELP_KDE_SUBSAMPLE);
	params->addFlag(ARG_AUTO_WINSIZE, DEFAULT_AUTO_WINSIZE, "", HELP_AUTO_WINSIZE);
	params->addFlag(ARG_AUTO_WINSIZE_STEP, DEFAULT_AUTO_WINSIZE_STEP, "", HELP_AUTO_WINSIZE_STEP);
	params->addFlag(ARG_BUILD, DEFAULT_BUILD, "", HELP_BUILD);
	params->addFlag(ARG_CENTROMERE_FILE, DEFAULT_CENTROMERE_FILE, "", HELP_CENTROMERE_FILE);

	params->setPreamble("Garlic v" + VERSION);

	if (!params->parseCommandLine(argc, argv))
	{
		delete params; 
		return NULL;
	}
	return params;
}

bool checkBuild(string BUILD)
{
	if (BUILD.compare("hg18") != 0 &&
	        BUILD.compare("hg19") != 0 &&
	        BUILD.compare("hg38") != 0 &&
	        BUILD.compare(DEFAULT_BUILD) != 0) {
		//cerr << "ERROR: Must choose hg18/hg19/hg38/none for build version.\n";
		LOG.err("ERROR: Must choose hg18/hg19/hg38 for build version or provide a custom centromere file.");
		return true;
	}
	return false;
}

bool checkBuildAndCentromereFile(string BUILD, string centromereFile){
	if(BUILD.compare(DEFAULT_BUILD) == 0 && centromereFile.compare(DEFAULT_CENTROMERE_FILE) == 0){
		LOG.err("ERROR: Must choose hg18/hg19/hg38 for build version or provide a custom centromere file.");
		return true;
	}
	return false;
}

bool checkMultiWinsizes(vector<int> &multiWinsizes, bool &WINSIZE_EXPLORE)
{
	if (multiWinsizes[0] != DEFAULT_WINSIZE_MULTI)
	{
		for (unsigned int i = 0; i < multiWinsizes.size(); i++)
		{
			if (multiWinsizes[i] <= 0)
			{
				//cerr << "ERROR: SNP window sizes must be > 1.\n";
				LOG.err("ERROR: SNP window sizes must be > 1.");
				return true;
			}
		}
		WINSIZE_EXPLORE = true;
	}
	return false;
}

bool checkAutoFreq(string freqfile, bool FREQ_ONLY, bool &AUTO_FREQ)
{
	if (freqfile.compare(DEFAULT_FREQ_FILE) != 0)
	{
		AUTO_FREQ = false;
		if (FREQ_ONLY)
		{
			//cerr << "ERROR: Specifying both " << ARG_FREQ_ONLY << " and " << ARG_FREQ_FILE << " accomplishes nothing useful.\n";
			LOG.err("ERROR: Specifying both", ARG_FREQ_ONLY, false);
			LOG.err(" and", ARG_FREQ_FILE, false);
			LOG.err(" accomplishes nothing useful.");
			return true;
		}
	}
	return false;
}

bool checkAutoWinsizeStep(int auto_winsize_step){
	if(auto_winsize_step <= 0){
		LOG.err("ERROR: Step size for automatic window selection must be positive.");
		return true;
	}
	return false;
}

bool checkAutoWinsize(bool WINSIZE_EXPLORE, bool AUTO_WINSIZE)
{
	//Check if both AUTO_WINSIZE and WINSIZE_EXPLORE are set
	//If so, exit with error.
	if (WINSIZE_EXPLORE && AUTO_WINSIZE)
	{
		//cerr << "ERROR: Must set only one of " << ARG_WINSIZE_MULTI << " and " << ARG_AUTO_WINSIZE << ".\n";
		LOG.err("ERROR: Must set only one of", ARG_WINSIZE_MULTI, false);
		LOG.err(" and", ARG_AUTO_WINSIZE);
		return true;
	}
	return false;
}

bool checkAutoCutoff(double LOD_CUTOFF, bool &AUTO_CUTOFF)
{
	if (LOD_CUTOFF != DEFAULT_LOD_CUTOFF) {
		AUTO_CUTOFF = false;
	}
	return false;
}

bool checkBoundSizes(vector<double> &boundSizes, bool &AUTO_BOUNDS)
{
	if (boundSizes[0] != DEFAULT_BOUND_SIZE && boundSizes.size() != 2) {
		//cerr << "ERROR: Must provide two bounds to " << ARG_BOUND_SIZE << endl;
		LOG.err("ERROR: Must provide two bounds to", ARG_BOUND_SIZE);
		return true;
	}
	else if (boundSizes.size() == 2)
	{
		double tmp;
		AUTO_BOUNDS = false;
		if (boundSizes[0] <= 0 || boundSizes[1] <= 0)
		{
			//cerr << "ERROR: User provided size boundaries must be positive.\n";
			LOG.err("ERROR: User provided size boundaries must be positive.");
			return true;
		}
		else if (boundSizes[0] > boundSizes[1])
		{
			tmp = boundSizes[0];
			boundSizes[0] = boundSizes[1];
			boundSizes[1] = tmp;
		}
		else if (boundSizes[0] == boundSizes[1])
		{
			//cerr << "ERROR: Size boundaries must be different.\n";
			LOG.err("ERROR: Size boundaries must be different.");
			return true;
		}
	}
	return false;
}

bool checkRequiredFiles(string tpedfile, string tfamfile)
{
	if (tpedfile.compare(DEFAULT_TPED) == 0 || tfamfile.compare(DEFAULT_TFAM) == 0)
	{
		//cerr << "ERROR: Must provide both a tped and a tfam file.\n";
		LOG.err("ERROR: Must provide both a tped and a tfam file.");
		return true;
	}
	return false;
}

bool checkThreads(int numThreads)
{
	if (numThreads <= 0)
	{
		//cerr << "ERROR: Number of threads must be > 0.\n";
		LOG.err("ERROR: Number of threads must be > 0.");
		return true;
	}
	return false;
}

bool checkError(double error)
{
	if (error <= 0 || error >= 1)
	{
		//cerr << "ERROR: Genotype error rate must be > 0 and < 1.\n";
		LOG.err("ERROR: Genotype error rate must be > 0 and < 1.");
		return true;
	}
	return false;
}

bool checkWinsize(int winsize)
{
	if (winsize <= 1)
	{
		//cerr << "ERROR: SNP window size must be > 1.\n";
		LOG.err("ERROR: SNP window size must be > 1.");
		return true;
	}
	return false;
}

bool checkMaxGap(int MAX_GAP)
{
	if (MAX_GAP < 0)
	{
		//cerr << "ERROR: Max gap must be > 0.\n";
		LOG.err("ERROR: Max gap must be > 0.");
		return true;
	}
	else if (MAX_GAP < 1000)
	{
		//cerr << "WARNING: max gap set very low: " << MAX_GAP << endl;
		//LOG.err("WARNING: max gap set very low:", MAX_GAP);
		LOG.err("WARNING: max gap set very low:", MAX_GAP);
	}
	return false;
}

bool checkOverlapFrac(double OVERLAP_FRAC){
	if(OVERLAP_FRAC <= 0 || OVERLAP_FRAC > 1){
		LOG.err("ERROR: Overlap fraction must be > 0 and <= 1.");
		return true;
	}
	return false;
}