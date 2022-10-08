DWTDelay : MultiOutUGen  {
	*ar {
		//arg m1(1.0), m2(1.0),m3(1.0),m4(1.0),m5(1.0),m6(1.0),m7(1.0),m8(1.0), gravity(0.1) ,dt(1.0), attenuation(0.1), maxDist(1000.0);
        arg ... args;
		^this.multiNewList((['audio']++(args[0].dereference)).flat);
		//^this.multiNew('audio', m1, m2, m3, m4, m5, m6, m7, m8, gravity, dt, attenuation, maxDist);
    }

	  init { | ... theInputs |
      inputs = theInputs
		^this.initOutputs(1, rate)
  }


}
