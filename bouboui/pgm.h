class FMZobi{
	int OPfreq;
	int OPmult;
	int OPlevel;
	int OPmode;
	int OPwave;
	AudioEffectEnvelope OPenv;
	int fdbk;

	static int algomix[32][6] = { //Algorithm mixers routing
		// 1     2     3     4     5	 6	  V1    V2    Alg Nb
		{1000, 0000, 1000, 1000, 0010, 0001, 1010, 0000,},   //1
		{1000, 0000, 1000, 1000, 0010, 0001, 1010, 0000,},   //1
	};
};
