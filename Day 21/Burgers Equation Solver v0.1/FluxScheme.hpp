/* This section of code will contain
 * the basic outline of the flux
 * discretization for the Burgers' equation
 * solution
 */
 
#ifndef FLUXSCHEME
#define FLUXSCHEME

class FluxScheme
{
	public:
	double Flux();
	double JacobianMatrix();
};

class Upwind: public FluxScheme
{
	public:
	double Flux();
};

class LaxFriedrichs: public FluxScheme
{
	public: 
	double Flux();
};

class LaxWendroff: public FluxScheme
{
	public:
	double Flux();
	double JacobianMatrix();
};

class MacCormack: public FluxScheme
{
	public:
	double PredictorStep();
	double CorrectorStep();
	double Flux();
};

#endif