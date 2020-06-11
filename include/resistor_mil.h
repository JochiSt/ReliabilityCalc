#ifndef RESISTOR_MIL_H
#define RESISTOR_MIL_H

#include "component.h"
/**
 * @brief Implementation of calculation for resistors
 */
class resistor_mil : public component {
 public:
  /**
   * @ingroup convUnits
   * @{
   */
  static constexpr float MOhm = 1;
  static constexpr float kOhm = 1. / 1000.;
  static constexpr float Ohm = 1. / (1000 * 1000);

  static constexpr float mW = 1. / 1000.;
  static constexpr float W = 1.;
  static constexpr float kW = 1000.;
  ///@}

  /*
    Resistor style, based on Military Handbook MIL-HDBK-217F
  */
  enum r_style_t {
    RC = 17,
    RCR = 17,
    RL = 37,
    RLR = 37,
    RN = 37,
    RM = 37,
    RD = 37,
    RZ = 19,
    RB = 24,
    RBR = 24,
    RW = 24,
    RWR = 24,
    RE = 24,
    RER = 24,
    RTH = 19,
    RT = 24,
    RTR = 24,
    RR = 24,
    RA = 24,
    RK = 24,
    RP = 24,
    RJ = 37,
    RJR = 37,
    RV = 37,
    RQ = 37,
    RVC = 37
  };

  /**
   * Resistor
   * \param name      part name e.g. R1
   * \param value     capacity value in MegaOhm
   * \param usedP     used power / applied power in Watt
   * \param ratedP    rated power in Watt
   */
  resistor_mil(std::string name, float value, float usedP, float ratedP, r_style_t r_sty);
  resistor_mil(std::string name, float value, float stress, r_style_t r_sty);
  resistor_mil() { partcnt--; };
  virtual ~resistor_mil(){};

  /**
   * @return resistance in MegaOhm
   */
  virtual float getResistance() { return resistance; }

  /**
   * set resistance
   * @param val resistance in Mega Ohm
   */
  virtual void setResistance(float val) { resistance = val; }

  /**
   * @brief calculate the FIT value for this component
   */
  virtual float getFIT();

  /// return the identifier
  static std::string getIdentifier() { return identifier; }

  /// get the part count
  static unsigned int getPartCount() { return partcnt; }

 protected:
  float resistance;  ///< resistance
  float usedPower;   ///< used Power in W
  float ratedPower;  ///< rated Power in W
  float style_factor;
  float temp_factor;
  float pow_factor;
  float stress_factor;
  float env_factor;
  float qual_factor;
  r_style_t style;

  float stress;  ///< used stress

 private:
  static std::string identifier;
  static unsigned int partcnt;
};

#endif  // RESISTOR_MIL_H
