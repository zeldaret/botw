#include "KingSystem/Resource/Actor/resResourceAwareness.h"

namespace ksys::res {

bool Awareness::parse_(u8* data, size_t, sead::Heap*) {
    addObj(&mBasisObj, "Basis");
    addObj(&mSightObj, "Sight");
    addObj(&mHearingObj, "Hearing");
    addObj(&mSenseObj, "Sense");
    addObj(&mWorryObj, "Worry");

    contactpoint_num.init(64, "contactpoint_num", "センサーに引っ掛けるバッファの数", &mBasisObj);
    base_node_name.init(sead::FixedSafeString<32>(""), "base_node_name", "前方基準ノード",
                        &mBasisObj);
    is_bind_rot.init(false, "is_bind_rot", "姿勢を追従させる", &mBasisObj);
    is_bind_pos.init(false, "is_bind_pos", "位置を追従させる", &mBasisObj);
    base_offset.init(sead::Vector3f::zero, "base_offset", "位置オフセット", &mBasisObj);
    base_dir.init(2, "base_dir", "基準方向", &mBasisObj);
    up_dir.init(6, "up_dir", "UP方向", &mBasisObj);
    awareness_target.init(sead::FixedSafeString<32>("一般敵"), "awareness_target", "種別設定",
                          &mBasisObj);
    interest_lv1_radius.init(5.0, "interest_lv1_radius", "興味値用接近距離", &mBasisObj);
    system_radius.init(0.0, "system_radius", "システム半径(プログラマ設定用)", &mBasisObj);
    invalidate_wheather_ratio.init(false, "invalidate_wheather_ratio", "天候影響無視", &mBasisObj);

    sight_buffer_num.init(32, "sight_buffer_num", "情報を格納するバッファの数", &mSightObj);
    sight_radius.init(15.0, "sight_radius", "発見水平範囲", &mSightObj);
    sight_angle.init(1.04719758034, "sight_angle", "発見有効角度", &mSightObj);
    sight_height_max.init(4.0, "sight_height_max", "発見垂直範囲最大", &mSightObj);
    sight_height_min.init(-2.0, "sight_height_min", "発見垂直範囲最小", &mSightObj);
    sight_height_near_max.init(4.0, "sight_height_near_max", "至近発見垂直範囲最大", &mSightObj);
    sight_height_near_min.init(-2.0, "sight_height_near_min", "至近発見垂直範囲最小", &mSightObj);
    sight_alert_radius.init(0.0, "sight_alert_radius", "警戒水平範囲", &mSightObj);
    sight_alert_angle.init(0.0, "sight_alert_angle", "警戒有効角度", &mSightObj);
    sight_alert_height_max.init(0.0, "sight_alert_height_max", "警戒垂直範囲最大", &mSightObj);
    sight_alert_height_min.init(0.0, "sight_alert_height_min", "警戒垂直範囲最小", &mSightObj);
    sight_alert_height_near_max.init(0.0, "sight_alert_height_near_max", "至近警戒垂直範囲最大",
                                     &mSightObj);
    sight_alert_height_near_min.init(0.0, "sight_alert_height_near_min", "至近警戒垂直範囲最小",
                                     &mSightObj);
    sight_ignore_grass_radius.init(2.0, "sight_ignore_grass_radius", "草無視範囲", &mSightObj);
    sight_delay_time_max.init(0, "sight_delay_time_max", "認識遅延時間最大", &mSightObj);
    sight_ray_check_range_max.init(-1.0, "sight_ray_check_range_max", "レイキャストの長さ制限値",
                                   &mSightObj);
    sight_base_node_name.init(sead::FixedSafeString<32>(""), "sight_base_node_name",
                              "(上書き用)前方基準ノード", &mSightObj);
    sight_far_use.init(false, "sight_far_use", "遠距離視界を使う", &mSightObj);
    sight_radius_far.init(0.0, "sight_radius_far", "遠距離開始距離", &mSightObj);
    sight_angle_far.init(1.04719758034, "sight_angle_far", "遠距離発見有効角度", &mSightObj);

    hearing_buffer_num.init(32, "hearing_buffer_num", "情報を格納するバッファの数", &mHearingObj);
    hearing_radius.init(15.0, "hearing_radius", "半径", &mHearingObj);
    hearing_notice_level.init(1.0, "hearing_notice_level", "発見状態になるノイズレベル",
                              &mHearingObj);
    hearing_alert_level.init(0.40000000596, "hearing_alert_level", "警戒状態になるノイズレベル",
                             &mHearingObj);
    hearing_blind_angle.init(0.0, "hearing_blind_angle", "死角角度", &mHearingObj);
    hearing_blind_margin_angle.init(0.0, "hearing_blind_margin_angle", "死角入り角度",
                                    &mHearingObj);
    hearing_reduce_ratio.init(0.0, "hearing_reduce_ratio", "死角に入られた際のノイズ反応倍率",
                              &mHearingObj);
    hearing_delay_time_max.init(0, "hearing_delay_time_max", "認識遅延時間最大", &mHearingObj);
    hearing_base_node_name.init(sead::FixedSafeString<32>(""), "hearing_base_node_name",
                                "(上書き用)前方基準ノード", &mHearingObj);

    sense_buffer_num.init(32, "sense_buffer_num", "情報を格納するバッファの数", &mSenseObj);
    sense_target.init(sead::FixedSafeString<32>("Enemy"), "sense_target", "テラー受付設定",
                      &mSenseObj);
    sense_radius_offset.init(0.0, "sense_radius_offset", "水平範囲オフセット", &mSenseObj);
    sense_angle.init(3.14159274101, "sense_angle", "有効角度", &mSenseObj);
    sense_delay_time_max.init(0, "sense_delay_time_max", "認識遅延時間最大", &mSenseObj);
    sense_base_node_name.init(sead::FixedSafeString<32>(""), "sense_base_node_name",
                              "(上書き用)前方基準ノード", &mSenseObj);

    worry_buffer_num.init(0, "worry_buffer_num", "情報を格納するバッファの数", &mWorryObj);
    worry_radius.init(0.0, "worry_radius", "範囲", &mWorryObj);
    worry_delay_time_max.init(0, "worry_delay_time_max", "認識遅延時間最大", &mWorryObj);
    worry_base_node_name.init(sead::FixedSafeString<32>(""), "worry_base_node_name",
                              "(上書き用)前方基準ノード", &mWorryObj);

    if (data)
        applyResParameterArchive(agl::utl::ResParameterArchive(data));

    return true;
}

}  // namespace ksys::res
