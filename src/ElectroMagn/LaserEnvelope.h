
#ifndef LaserENVELOPE_H
#define LaserENVELOPE_H

#include <vector>
#include <complex>

#include "Params.h"
#include "Patch.h"

class Field;
class ElectroMagn;
class Profile;
class EnvelopeBC;
class SimWindow;

// Class for envelope
class LaserEnvelope
{
public:
    LaserEnvelope( Params &params, Patch *patch, ElectroMagn *EMfields ); // Main constructor
    LaserEnvelope( LaserEnvelope *envelope, Patch *patch, ElectroMagn *EMfields, Params &params, unsigned int n_moved ); // Cloning constructor
    virtual void initEnvelope( Patch *patch, ElectroMagn *EMfields ) = 0;
    virtual ~LaserEnvelope();
    virtual void compute( ElectroMagn *EMfields ) = 0;
    virtual void compute_Phi( ElectroMagn *EMfields ) = 0;
    virtual void compute_gradient_Phi( ElectroMagn *EMfields ) = 0;
    void boundaryConditions( int itime, double time_dual, Patch *patch, Params &params, SimWindow *simWindow );
    virtual void savePhi_and_GradPhi() = 0;
    virtual void centerPhi_and_GradPhi() = 0;
    
    Profile *profile_;
    const std::vector<double> cell_length;
    const double timestep;
    double polarization_phi;
    double ellipticity;
    
    Field *A_;         // envelope value at timestep n
    Field *A0_;        // envelope value at timestep n-1
    
    Field *Phi_;       // ponderomotive potential Phi=|A|^2/2 value at timestep n
    Field *GradPhix_;  // x component of the gradient of Phi at timestep n
    Field *GradPhiy_;  // y component of the gradient of Phi at timestep n
    Field *GradPhiz_;  // z component of the gradient of Phi at timestep n
    Field *GradPhil_;  // l component of the gradient of Phi at timestep n
    Field *GradPhir_;  // r component of the gradient of Phi at timestep n
    
    // Correspondent time-centered quantities
    Field *Phi_m;
    Field *GradPhix_m;
    Field *GradPhiy_m;
    Field *GradPhiz_m;
    Field *GradPhil_m;
    Field *GradPhir_m;
    
    //! Vector of boundary-condition per side for the envelope field
    std::vector<EnvelopeBC *> EnvBoundCond;
    //EnvBoundCond = EnvelopeBC_Factory::create(params, patch);
    
    std::complex<double> i1_2k0_over_2dx, one_plus_ik0dt, one_plus_ik0dt_ov_one_plus_k0sq_dtsq,i1_2k0_over_2dl;
};

// Class for envelope
class LaserEnvelope1D : public LaserEnvelope
{
public:
    LaserEnvelope1D( Params &params, Patch *patch, ElectroMagn *EMfields );
    LaserEnvelope1D( LaserEnvelope *envelope, Patch *patch, ElectroMagn *EMfields, Params &params, unsigned int n_moved );
    void initEnvelope( Patch *patch, ElectroMagn *EMfields ) override final;
    ~LaserEnvelope1D();
    void compute( ElectroMagn *EMfields ) override final;
    void compute_Phi( ElectroMagn *EMfields ) override final;
    void compute_gradient_Phi( ElectroMagn *EMfields ) override final;
    void savePhi_and_GradPhi() override final;
    void centerPhi_and_GradPhi() override final;
};

// Class for envelope
class LaserEnvelope2D : public LaserEnvelope
{
public:
    LaserEnvelope2D( Params &params, Patch *patch, ElectroMagn *EMfields );
    LaserEnvelope2D( LaserEnvelope *envelope, Patch *patch, ElectroMagn *EMfields, Params &params, unsigned int n_moved );
    void initEnvelope( Patch *patch, ElectroMagn *EMfields ) override final;
    ~LaserEnvelope2D();
    void compute( ElectroMagn *EMfields ) override final;
    void compute_Phi( ElectroMagn *EMfields ) override final;
    void compute_gradient_Phi( ElectroMagn *EMfields ) override final;
    void savePhi_and_GradPhi() override final;
    void centerPhi_and_GradPhi() override final;
};

// Class for envelope
class LaserEnvelope3D : public LaserEnvelope
{
public:
    LaserEnvelope3D( Params &params, Patch *patch, ElectroMagn *EMfields );
    LaserEnvelope3D( LaserEnvelope *envelope, Patch *patch, ElectroMagn *EMfields, Params &params, unsigned int n_moved );
    void initEnvelope( Patch *patch, ElectroMagn *EMfields ) override final;
    ~LaserEnvelope3D();
    void compute( ElectroMagn *EMfields ) override final;
    void compute_Phi( ElectroMagn *EMfields ) override final;
    void compute_gradient_Phi( ElectroMagn *EMfields ) override final;
    void savePhi_and_GradPhi() override final;
    void centerPhi_and_GradPhi() override final;
};

// Class for envelope with cylindrical symmetry
class LaserEnvelopeAM : public LaserEnvelope
{
public:
    LaserEnvelopeAM( Params &params, Patch *patch, ElectroMagn *EMfields );
    LaserEnvelopeAM( LaserEnvelope *envelope, Patch *patch, ElectroMagn *EMfields, Params &params, unsigned int n_moved );
    void initEnvelope( Patch *patch, ElectroMagn *EMfields ) override final;
    ~LaserEnvelopeAM();
    void compute( ElectroMagn *EMfields ) override final;
    void compute_Phi( ElectroMagn *EMfields ) override final;
    void compute_gradient_Phi( ElectroMagn *EMfields ) override final;
    void savePhi_and_GradPhi() override final;
    void centerPhi_and_GradPhi() override final;
};



#endif
