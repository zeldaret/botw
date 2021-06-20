#include "KingSystem/Chemical/chmSystemConfig.h"

namespace ksys::chm {

SystemConfig::Element::Element()
    : name({"----"}, "name", "ID", this), label({"名称未設定"}, "label", "名前", this),
      effect_type(0, "effect_type", "エフェクトタイプ", this),
      attribute(0, "attribute", "ビットフラグ", this),
      life_frames(0.0, "life_frames", "寿命（フレーム）", "Min=0.0 ,Max=300", this),
      temperature(0.0, "temperature", "温度", this), type(2, "type", "タイプ", this),
      wetting_rate(0.0, "wetting_rate", "濡れ率", this),
      wind_speed(0.0, "wind_speed", "風速", this),
      electric_charge(0.0, "electric_charge", "電荷", this),
      shock_wave_speed(0.0, "shock_wave_speed", "衝撃波の速度", this),
      fire_level(2, "fire_level", "炎レベル", this), moisture(0.0, "moisture", "湿度", this) {}

SystemConfig::Element::~Element() = default;

SystemConfig::Material::Material()
    : id({"untitled"}, "id", "ID", this), label({"名称未設定材質"}, "label", "名前", this),
      attribute(0, "attribute", "属性フラグ", this),
      heat_capacity(1.0, "heat_capacity", "比熱容量[J/gK]", "Min=0, Max=10", this),
      thermal_conductivity(1.0, "thermal_conductivity", "熱伝導率[W/m・K]", "Min=0, Max=100", this),
      electrical_resistivity(1.0, "electrical_resistivity", "電気抵抗率[Ω・m]", "Min=-10, Max=10",
                             this),
      electrical_capacitance(1.0, "electrical_capacitance", "静電容量[F]", "Min=0, Max=1", this),
      electromotive_force(0.0, "electromotive_force", "起電力[V]", "Min=0, Max=10", this),
      fire_proof_level(0, "fire_proof_level", "耐火性能[Lv]", "Min=0, Max=5", this),
      ignition_point(100.0, "ignition_point", "発火点(度)", "Min=0 ,Max=1000", this),
      burn_speed(1.0, "burn_speed", "燃える速度", "Min=0 ,Max=1.0", this),
      wetting_amount(1.0, "wetting_amount", "単位面積あたりの塗れ量[kg/m2]", "Min=0, Max=100",
                     this),
      wind_force_remain_rate(0.0, "wind_force_remain_rate", "風力影響の残り率", "Min=0,Max=1",
                             this),
      burn_res_element_name({"----"}, "burn_res_element_name", "炎", this),
      warm_res_element_name({"----"}, "warm_res_element_name", "暖気", this),
      exp_res_element_name({"----"}, "exp_res_element_name", "爆発(slot0)", this),
      exp_res_element_name1({"----"}, "exp_res_element_name1", "爆発(slot1)", this),
      electricity_res_element_name({"----"}, "electricity_res_element_name", "帯電", this),
      ice_magic_res_element_name({"----"}, "ice_magic_res_element_name", "氷魔法", this),
      water_res_element_name({"----"}, "water_res_element_name", "水", this) {}

SystemConfig::Material::~Material() = default;

SystemConfig::World::World()
    : id({"untitled"}, "id", "ID", this), label({"名称未設定"}, "label", "ラベル", this),
      evaporation_speed_rate(24.0, "evaporation_speed_rate", "温度に対する蒸発係数",
                             "Min=0 ,Max=100", this),
      heat_transfer_speed_rate(24.0, "heat_transfer_speed_rate", "伝熱速度倍率(全体)", this),
      fire_heat_transfer_speed_rate(2.0, "fire_heat_transfer_speed_rate", "伝熱速度倍率(炎)", this),
      conduction_speed_rate_log(-5.0, "conduction_speed_rate_log", "電気伝導速度倍率", this),
      burn_speed_rate(0.1, "burn_speed_rate", "燃焼速度倍率", this),
      fire_extra_radius(0.3, "fire_extra_radius", "炎は何m離れてても当たるか", this),
      player_fire_margin(0.3, "player_fire_margin", "プレイヤーの直火大丈夫距離[m]", this),
      electricity_extra_radius_rate(50.0, "electricity_extra_radius_rate", "放電距離倍率", this),
      electric_water_extra_radius_rate(500.0, "electric_water_extra_radius_rate",
                                       "放電距離倍率(水の漏電)", this),
      min_ice_size(0.15, "min_ice_size", "最少の氷サイズ[m]", this),
      ice_heat_cheat_threshold(10000.0, "ice_heat_cheat_threshold",
                               "氷を溶けやすくするチートの発動重要[kg]", this),
      ice_heat_cheat_rate(0.5, "ice_heat_cheat_rate", "氷を溶けやすくするチートの割合", this),
      ice_melt_ratio_env_temp(0.05, "ice_melt_ratio_env_temp", "氷解率vs気温", this),
      ice_melt_ratio_warm_air(0.5, "ice_melt_ratio_warm_air", "氷解率vs暖気", this),
      ice_melt_ratio_fire(1.0, "ice_melt_ratio_fire", "氷解率vs火", this),
      ice_melt_ratio_fire2(10.0, "ice_melt_ratio_fire2", "氷解率vs炎", this),
      wind_lift_rate(0.1, "wind_lift_rate", "揚抗比", this),
      lightning_distance(25.0, "lightning_distance", "落雷の範囲[m]", this),
      character_ignition_count(90.0, "character_ignition_count", "キャラクタ着火時間(フレーム)",
                               this),
      object_ignition_count(90.0, "object_ignition_count", "キャラクタ着火時間(フレーム)", this),
      offensive_rigid_radius(1.0, "offensive_rigid_radius", "攻撃状態のケミカルサイズ", this) {}

SystemConfig::World::~World() = default;

}  // namespace ksys::chm
