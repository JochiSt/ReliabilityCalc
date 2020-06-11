#ifndef CAPACITOR_MIL_H
#define CAPACITOR_MIL_H

#include "component.h"

/**
 * @brief Implementation of reliability of capacitors
 */
class capacitor_mil : public component {
 public:
  /**
   * @addtogroup convUnits convenience definitions of units
   * @{
   */
  static constexpr float pF = 1.;
  static constexpr float nF = 1000.;
  static constexpr float uF = 1000. * 1000.;

  static constexpr float V = 1.;
  static constexpr float mV = 1. / 1000.;
  static constexpr float kV = 1000.;
  ///@}

  /**
   * Type of capacitor, based on Military Handbook MIL-HDBK-217F
   **/
  enum style_t {
    CP = 370000,
    CA = 370000,
    CZ = 370000,
    CQ = 510000,
    CH = 370000,
    CHR = 510000,
    CFR = 510000,
    CRH = 510000,
    CM = 760000,
    CMR = 760000,
    CB = 760000,
    CY = 760000,
    CYR = 760000,
    CK = 990000,
    CKR = 990000,
    CC = 990000,
    CDR = 2000000,
    CSR = 400000,
    CWR = 50000,
    CL = 400000,
    CLR = 400000,
    CRL = 400000,
    CU = 120000,
    CE = 120000,
    CV = 7900000,
    PC = 6000000,
    CT = 72,
    CG = 6000000
  };

  /**
   * Constructor of Capacitor
   * \param name      internal naming of capacitor, e.g. C1, C2
   * \param value     capacity value in pF
   * \param usedU     used voltage / applied voltage
   * \param ratedU    rated voltage
   */
  capacitor_mil(std::string name, float value, float usedU, float ratedU,
            style_t sty);

  capacitor_mil(std::string name, float value, float stress, style_t sty);

  virtual ~capacitor_mil();

  /// @return stress
  float getStress() { return stress; }

  /// @return capacity in pF
  float getCapacity() { return capacity; }
  /**
   * @param val capacity in pF
   */
  void setCapacity(float val) { capacity = val; }

  /// @return FIT of this specific component
  virtual float getFIT();

  /// get capacitor identifier
  static std::string getIdentifier() { return identifier; }
  /// get the capacitor part count
  static unsigned int getPartCount() { return partcnt; }

 protected:
  float capacity;      ///< capacity in pF
  float usedVoltage;   ///< voltage applied to the capacitor
  float ratedVoltage;  ///< rated voltage of the capacitor

  float stress;  ///< stress level of this capacitor ( usedVoltage /
                 ///< ratedVoltage )

  style_t style;

  float style_factor;
  float temp_factor;
  float cap_factor;
  float volt_factor;
  float res_factor;
  float qual_factor;
  float env_factor;

 private:
  static std::string identifier;  ///< store capacitor identifier
  static unsigned int partcnt;    ///< static variable for counting the parts
};

#endif  // CAPACITOR_H
