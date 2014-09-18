/*THIS IS CLIPPED FROM 
  	~/PSUADE/Src/DataIO
  And will not work on its own. It's only here for reference.
*/


// ************************************************************************
// A function for reading PSUADE IO data
// ------------------------------------------------------------------------ 
void PsuadeData::readPsuadeIO(const char *fname) 
{
   int    nInputs, nOutputs, *sampleStates, nSamples, ss, ii, idata;
   double *sampleInputs, *sampleOutputs;
   char   lineInput[500], keyword[500];
   FILE   *fIn;

   fIn = fopen(fname, "r");
   assert(fIn != NULL);
   fgets(lineInput, 500, fIn);
   sscanf(lineInput, "%s", keyword);
   while (keyword[0] == '#')
   {
      fgets(lineInput, 500, fIn);
      sscanf(lineInput, "%s", keyword);
   }
   if (!strcmp(keyword, "PSUADE_IO")) /* data is in this section */
   {
      fscanf(fIn, "%d %d %d\n", &nInputs, &nOutputs, &nSamples);
      if (nInputs <= 0 || nOutputs <= 0 || nSamples <= 0)
      {
         printf("readPsuadeIO ERROR: first parameters <= 0.\n");
         exit(1);
      }
      sampleInputs  = new double[nInputs*nSamples];
      sampleOutputs = new double[nOutputs*nSamples];
      sampleStates  = new int[nSamples];
      for (ss = 0; ss < nSamples; ss++)
      {
         fscanf(fIn,"%d %d", &idata, &sampleStates[ss]);
         if (idata != (ss+1))
         {
            printf("readPsuadeIO ERROR: incorrect sample no.\n");
            printf("        Incoming/expected sample number = %d %d\n",
                   idata, ss+1);
            exit(1);
         }
         if (sampleStates[ss] != 1) sampleStates[ss] = 0;
         for (ii = 0; ii < nInputs; ii++) 
            fscanf(fIn,"%lg",&sampleInputs[ss*nInputs+ii]);
         for (ii = 0; ii < nOutputs; ii++) 
            fscanf(fIn,"%lg",&sampleOutputs[ss*nOutputs+ii]);
      }
      pInput_.nInputs_        = nInputs;
      pInput_.sampleInputs_   = sampleInputs;
      pOutput_.nOutputs_      = nOutputs;
      pOutput_.sampleOutputs_ = sampleOutputs;
      pOutput_.sampleStates_  = sampleStates;
      pMethod_.nSamples_      = nSamples;
      if (outputLevel_ > 1)
      {
         printf("readPsuadeIO: read sample data completed.\n");
         printf("   nInputs, nOutputs, nSamples = %d %d %d\n", nInputs, 
                nOutputs, nSamples);
      }
   }
   else
   {
      if (outputLevel_ > 0)
         printf("readPsuadeIO: PSUADE_IO section absent.\n");
   }
   fclose(fIn);
}
