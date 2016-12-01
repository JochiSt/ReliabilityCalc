#include "component_MIL_HDBK_217F.h"

component_MIL_HDBK_217F::calc_method_t component_MIL_HDBK_217F::calculation_method = MIL_HDBK_217F; // for normal use MIL HDBK without notice
component_MIL_HDBK_217F::environment_t component_MIL_HDBK_217F::environment = GB;

component_MIL_HDBK_217F::component_MIL_HDBK_217F(std::string name) : component(name){

}
