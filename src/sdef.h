#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include "hash.h"
#include "thirdparty/json/json.hpp"

class sdef
{
public:
	sdef();
	sdef(uint64_t rpkgs_index, uint64_t hash_index);
	sdef(std::string json_path, uint64_t hash_value, std::string output_path, bool output_path_is_file);
	sdef(std::string sdef_path, std::string sdef_meta_path, uint64_t hash_value, std::string output_path, bool output_path_is_file);

	void generate_json(std::string output_path);

	std::string sdef_file_name = "";
	uint32_t sdef_rpkg_index = 0;
	uint32_t sdef_hash_index = 0;
	std::vector<char> sdef_input_data;
	std::vector<char> sdef_output_data;
	std::vector<char> sdef_data;
	uint32_t sdef_entry_count = 0;
	hash meta_data;
	nlohmann::ordered_json json;
	std::string json_error = "";
	std::vector<std::string> slots = { "",
									"dth_brknck",
									"dth_fll",
									"dth_gnsht",
									"dth_hdsht",
									"dth_mpct",
									"dth_sltthrt",
									"dth_strngl",
									"dth_xplo",
									"dth_prpf",
									"dth_electro",
									"dth_burn",
									"dth_crush",
									"",
									"dth_hrt",
									"dth_srpsgrab",
									"dth_humshldstrain",
									"dth_snore",
									"dth_groan",
									"dth_dump",
									"dth_prptssfrntack",
									"dth_headlock",
									"dth_blinded",
									"dth_beesting",
									"",
									"gen_grt47",
									"gen_grtgrd47wgun",
									"",
									"",
									"gen_npc2npcgrt",
									"",
									"gen_gthlp",
									"gen_gthlpld",
									"gen_gthlp47knwn",
									"gen_mssng",
									"gen_hmhere",
									"gen_hmthere",
									"gen_srpslow",
									"gen_srpslowshort",
									"gen_srps",
									"gen_srpsld",
									"gen_stndrsp",
									"gen_stop",
									"gen_stopld",
									"gen_reveal",
									"gen_thumbsup",
									"gen_brknack",
									"gen_ack",
									"gen_ackld",
									"gen_ackntnse",
									"gen_bumpack",
									"gen_curse",
									"gen_curselow",
									"gen_drpgun",
									"gen_drpcase",
									"gen_coincurse",
									"gen_transportgreet",
									"gen_thanks",
									"gen_returnitem2guard",
									"gen_noway1",
									"gen_noway2kidding",
									"gen_noway3joke",
									"gen_noway44real",
									"gen_noway5dntbeliv",
									"gen_noway6serious",
									"gen_noway7horrible",
									"gen_way1",
									"gen_way2kidding",
									"gen_way3joke",
									"gen_way44real",
									"gen_way5dntbeliv",
									"gen_way6serious",
									"gen_way7horrible",
									"gen_nkdrunack",
									"gen_grasp",
									"gen_amused",
									"gen_annoyed",
									"",
									"",
									"gen_giveup",
									"gen_off",
									"gen_on",
									"gen_paniclow",
									"gen_sick",
									"gen_smellack",
									"gen_smrtphnact",
									"gen_phoneact",
									"gen_outbreakinfect",
									"gen_outbreaksick",
									"gen_outbreakwhine",
									"",
									"clscmbt_ack",
									"clscmbt_tnt",
									"cmbt_backupcll",
									"cmbt_baddsg",
									"cmbt_beg",
									"cmbt_clsack",
									"cmbt_fire",
									"cmbt_fireldr",
									"cmbt_gthit",
									"cmbt_hithm",
									"cmbt_hmclscmbtack",
									"cmbt_hmcvr",
									"cmbt_hmfire",
									"cmbt_hmflnk",
									"cmbt_hmheadpopr",
									"cmbt_hmkll",
									"cmbt_hmkllciv",
									"cmbt_hmkllname",
									"cmbt_hmkllprptss",
									"cmbt_hmmsstnt",
									"cmbt_hmshrpshtr",
									"bad47spttd_gtag",
									"cmbt_hmvnshd",
									"cmbt_hold",
									"cmbt_holdldr",
									"",
									"",
									"",
									"",
									"",
									"",
									"",
									"",
									"cmbt_lnglst",
									"cmbt_lnglstrsp",
									"cmbt_lstmnstn",
									"cmbt_lstsght",
									"cmbt_lstsghtrsp",
									"cmbt_ndrattck",
									"cmbt_relod",
									"cmbt_scrm",
									"cmbt_throwflash",
									"cmbt_throwflashmiss",
									"cmbt_throwflashmiss2",
									"cmbt_throwflashwin",
									"cmbt_throwflashwin2",
									"cmbt_tkdwnldr",
									"",
									"cmbt_whmp",
									"cmbt_stalematehold",
									"cmbt_stalematetnt",
									"cmbt_triggerthealarm",
									"cmbt_47mpty",
									"cmbt_47supersize",
									"evac_prttrgtsolo",
									"evac_prttrgtack",
									"evac_prttrgtackldr",
									"evac_prttrgtescrt",
									"evac_prttrgtstop",
									"evac_prttrgtstnd",
									"evac_prttrgtstndrsp",
									"evac_cornered",
									"evac_movout",
									"evac_pathchange",
									"evac_peeloff",
									"evac_lastpeeloff",
									"evac_shltrarrv",
									"evac_shltrbad",
									"evac_shltrldr",
									"evac_shltrrsp",
									"evac_trgthitrsp",
									"avoidxplo_ack",
									"avoidxplo_stnd",
									"ar_47badaction",
									"ar_47x",
									"ar_baddsga",
									"ar_blmekll",
									"ar_blameknckdwn",
									"ar_blameknckdwnpt",
									"ar_blamekllpt",
									"ar_47badactionpt",
									"ar_drgbody",
									"ar_fkesrrdrtnt",
									"ar_hmdoor",
									"ar_strangle",
									"ar_trspss",
									"ar_weapwrn1a",
									"ar_weapwrn2a",
									"ar_wrn1",
									"ar_wrn2",
									"ar_wrn3",
									"ar_victimack",
									"ar_thief",
									"ar_rsp",
									"sniper_ack",
									"inca_backupcll",
									"inca_chckcvr",
									"inca_civrptfail",
									"inca_civupset",
									"inca_clsttnt",
									"inca_hmtnt",
									"inca_idle",
									"inca_nitiatehmknwn",
									"inca_srchldr",
									"inca_stnd",
									"inca_stndagtd",
									"inca_stndagtdldr",
									"inca_stndagtdhmknwn",
									"inca_stndagtdhmknwnldr",
									"inca_stndhmknwn",
									"inca_stndhmknwnldr",
									"inca_stndldr",
									"inca_stndrsp",
									"",
									"inca_vnttnt",
									"inca_brk2civ",
									"inca_brk2grd",
									"inca_brk2rdo",
									"inca_brkask",
									"inca_ghostask",
									"inca_triggerthealarm",
									"inca_xpln47thief",
									"inca_dstrssinv",
									"inca_dstrssldr",
									"inca_dstrssinvldr",
									"inca_wakeask",
									"inca_47rcall",
									"inca_wakerstnd",
									"",
									"inca_seedthinv",
									"inca_seedthinvldr",
									"inca_seedthldr",
									"inca_xploinv",
									"inca_xploinvldr",
									"inca_xploldr",
									"inca_alarmack",
									"inca_gnshtinv",
									"inca_gnshtinvldr",
									"inca_gnshtldr",
									"inca_recursvrinv",
									"inca_recursvrinvldr",
									"inca_recursvrinvrsp",
									"inca_recursvrldr",
									"inca_recursvrrsp",
									"inca_lckdwngtoutldr",
									"inca_lckdwngtoutrsp",
									"",
									"",
									"",
									"",
									"inca_frskack",
									"inca_frsk",
									"inca_frskcln",
									"inca_frskwpn",
									"inca_xpln47wpn",
									"inca_xplnaccdnt",
									"xplnbdy",
									"inca_xplndedbdymassive",
									"inca_xplndrgbdy",
									"inca_xplndstrss",
									"inca_xplnexplo",
									"inca_xplnghost",
									"inca_xplngnsht",
									"inca_xplnnkdbdy",
									"xplnpcfdbdy",
									"inca_xplnseedth",
									"inca_xplntrspss",
									"inca_xplnx",
									"inca_xplnwpn",
									"inca_xplndsg",
									"inca_xplnimposter",
									"inca_xplnrecursvr",
									"inca_xplnrsp",
									"inca_xplnackrdo",
									"inca_xplnknckdwn",
									"inca_xplnknckdwnvctm",
									"inca_xplnknckdwnghost",
									"inca_xplnseestrngl",
									"inca_xplnhunttargetwin",
									"inca_xplnhunttargetfail",
									"inca_vipdownack",
									"inca_vipkillack",
									"accdnt_inv",
									"indedbdy_bloodpllack",
									"indedbdy_ack",
									"indedbdy_nkdack",
									"indedbdy_inv",
									"",
									"indedbdy_massive",
									"indedbdy_pcfdinv",
									"indedbdy_cntnack",
									"",
									"",
									"indedbdy_civcmnt",
									"indedbdy_prmtrbrchwrn1",
									"indedbdy_prmtrbrchwrn2",
									"indedbdy_47asgrdack",
									"indedbdy_bodygone",
									"indedbdy_vctmrcvr",
									"indedbdy_wakerwake",
									"indedbdy_wakersp",
									"indedbdy_wakenkdldr",
									"indedbdy_wakenkdrsp",
									"",
									"",
									"rcvr_xplnknckdwn",
									"indsg_fllwwrn1",
									"indsg_fllwwrn2",
									"indsg_fllwwrn3",
									"indsg_pzzl",
									"indsg_stnd",
									"indsg_stnddistance",
									"indsg_stndhidden",
									"indsg_hdnplnsght",
									"indsg_fllwwrn1ackdsg",
									"indsg_fllwwrn1badaction",
									"indsg_fllwwrn1wpn",
									"indsg_fllwwrn1badsound",
									"indsg_fllwwrnjoinr",
									"indsg_fllwwrn1shadyitem",
									"trspss_stnd",
									"trspss_wrn1",
									"trspss_wrn2",
									"trspss_wrn3",
									"trspss_rsp",
									"trspss_srchacklegal47",
									"trspss_escortack",
									"trspss_escortrequest",
									"trspss_escortrequestrepeat",
									"trspss_escortstayclose",
									"trspss_escortok",
									"trspss_escortstnd",
									"trspss_escortarrest",
									"trspss_escortexit",
									"trspss_escortstayrequest",
									"incu_brk2rdo",
									"incu_civcmnd",
									"incu_stnd",
									"incu_civrsp",
									"incu_backuprqst",
									"incu_cralrmack",
									"incu_cralrmldr",
									"incu_cralrmstndrsp",
									"gen_srps,incu_ftstpsack",
									"incu_stnd,incu_ftstpsstnd",
									"incu_prptsshearack",
									"incu_prptsshearinv",
									"incu_prptsshearldr",
									"incu_prptsshearstndrsp",
									"incu_prptssseeack",
									"incu_prptssseeinv",
									"incu_prptssseeldr",
									"incu_prptssseestndrsp",
									"incu_rdoack",
									"",
									"incu_rdoldr",
									"incu_rdostndrsp",
									"incu_wpninv",
									"incu_recurack",
									"incu_recurinv",
									"incu_recurldr",
									"incu_recurrsp",
									"incu_itemackldr",
									"",
									"incu_escrttrgtredlight",
									"incu_escrttrgtgreenlight",
									"inst_hmaglty",
									"inst_hmbz",
									"inst_hmbzstnd",
									"inst_hmentxit",
									"inst_hmincvr",
									"inst_hmsnkng",
									"inst_prptsssee",
									"inst_stnd",
									"inst_wrn",
									"inst_hm2cls",
									"inst_sickacknormal",
									"inst_adiosrequest",
									"inst_pq",
									"fsebx_fixed",
									"fsebx_fixing",
									"fsebx_gofix",
									"fsebx_saback",
									"sentry_denyentry",
									"sentry_frsk",
									"sentry_frskrequest",
									"sentry_itemrequest",
									"sentry_accepted",
									"sentry_frskwpnack",
									"sentry_47loiterack",
									"sentry_denydsg",
									"sentry_postcommentldr",
									"sentry_postcommentrsp",
									"",
									"",
									"",
									"",
									"vipmsnngcallout",
									"dth_sick",
									"dth_poison",
									"gen_avoid",
									"gen_closecall",
									"gen_phnpckup",
									"gen_phoneactlockdown",
									"cmbt_flushoutldr",
									"cmbt_hmprptssknckout",
									"inca_frskheadsupldr",
									"inca_frskheadsuprdo",
									"inca_xplnlos",
									"inca_xplngotshot",
									"indedbdy_civcmntphone",
									"",
									"indsg_fllwwrn1nkd",
									"ar_blameknckdwnmelee",
									"",
									"exp_clearthroat",
									"exp_cough",
									"exp_drink",
									"exp_exhale",
									"exp_idle",
									"exp_inhale",
									"exp_inhalefast",
									"exp_sniff",
									"exp_swallow",
									"exp_think",
									"exp_scared",
									"exp_gld",
									"exp_dsppntd",
									"exp_inpain",
									"inca_ackbdy",
									"inca_ackbdyldr",
									"indedbdy_civcmntpcfd",
									"indedbdy_civcmntphonepcfd",
									"gen_socialack" };
};