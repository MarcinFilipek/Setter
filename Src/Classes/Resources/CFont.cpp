/*
 * CFont.cpp
 *
 *  Created on: Sep 29, 2015
 *      Author: krzysiek
 */

#include "CFont.h"
#include "CImgData.h"

const CGraphicFont::TImgCharMap CFont::CHAR_MAP_FONT_1[] =
{
{'°', CImgData::IMG_FONT1_ST_CELCIUSZ},
{'@', CImgData::IMG_FONT1_MALPA},
{' ', CImgData::IMG_FONT1_SPACJA},
{' ', CImgData::IMG_FONT1_SPACJA},
{'!', CImgData::IMG_FONT1_WYKRZYKNIK},
{'"', CImgData::IMG_FONT1_CUDZYSLOW},
{'#', CImgData::IMG_FONT1_HASZ},
{'$', CImgData::IMG_FONT1_DOLAR},
{'%', CImgData::IMG_FONT1_PROCENT},
{'&', CImgData::IMG_FONT1_AMPERSAND},
{'\'', CImgData::IMG_FONT1_APOSTROF},
{'ʹ', CImgData::IMG_FONT1_APOSTROF},
{'(', CImgData::IMG_FONT1_NAWIAS_OKRAGLY_LEWY},
{')', CImgData::IMG_FONT1_NAWIAS_OKRAGLY_PRAWY},
{'*', CImgData::IMG_FONT1_GWIAZDKA},
{'+', CImgData::IMG_FONT1_PLUS},
{',', CImgData::IMG_FONT1_PRZECINEK},
{'-', CImgData::IMG_FONT1_MINUS},
{'_', CImgData::IMG_FONT1_PODKRESLNIK},
{'–', CImgData::IMG_FONT1_MINUS},
{'.', CImgData::IMG_FONT1_KROPKA},
{'/', CImgData::IMG_FONT1_SLASH},
{':', CImgData::IMG_FONT1_DWUKROPEK},
{';', CImgData::IMG_FONT1_SREDNIK},
{'<', CImgData::IMG_FONT1_MNIEJSZY},
{'=', CImgData::IMG_FONT1_ROWNY},
{'>', CImgData::IMG_FONT1_WIEKSZY},
{'?', CImgData::IMG_FONT1_ZAPYTAJNIK},
{'^', CImgData::IMG_FONT1_DASZEK},
{'±', CImgData::IMG_FONT1_PLUS_MINUS},
{'\\', CImgData::IMG_FONT1_BACKSLASH},
{'[', CImgData::IMG_FONT1_NAWIAS_PROSTOK_LEWY},
{']', CImgData::IMG_FONT1_NAWIAS_PROSTOK_PRAWY},
{'¿', CImgData::IMG_FONT1_PYTAJNIK_OBROCONY},

{'0', CImgData::IMG_FONT1_0},
{'1', CImgData::IMG_FONT1_1},
{'2', CImgData::IMG_FONT1_2},
{'3', CImgData::IMG_FONT1_3},
{'4', CImgData::IMG_FONT1_4},
{'5', CImgData::IMG_FONT1_5},
{'6', CImgData::IMG_FONT1_6},
{'7', CImgData::IMG_FONT1_7},
{'8', CImgData::IMG_FONT1_8},
{'9', CImgData::IMG_FONT1_9},

{'a', CImgData::IMG_FONT1_a},
{'A', CImgData::IMG_FONT1_A},

{'b', CImgData::IMG_FONT1_b},
{'B', CImgData::IMG_FONT1_B},

{'c', CImgData::IMG_FONT1_c},
{'C', CImgData::IMG_FONT1_C},

{'d', CImgData::IMG_FONT1_d},
{'D', CImgData::IMG_FONT1_D},

{'e', CImgData::IMG_FONT1_e},
{'E', CImgData::IMG_FONT1_E},

{'f', CImgData::IMG_FONT1_f},
{'F', CImgData::IMG_FONT1_F},

{'g', CImgData::IMG_FONT1_g},
{'G', CImgData::IMG_FONT1_G},

{'h', CImgData::IMG_FONT1_h},
{'H', CImgData::IMG_FONT1_H},

{'i', CImgData::IMG_FONT1_i},
{'I', CImgData::IMG_FONT1_I},

{'j', CImgData::IMG_FONT1_j},
{'J', CImgData::IMG_FONT1_J},

{'k', CImgData::IMG_FONT1_k},
{'K', CImgData::IMG_FONT1_K},

{'l', CImgData::IMG_FONT1_l},
{'L', CImgData::IMG_FONT1_L},

{'m', CImgData::IMG_FONT1_m},
{'M', CImgData::IMG_FONT1_M},

{'n', CImgData::IMG_FONT1_n},
{'N', CImgData::IMG_FONT1_N},

{'o', CImgData::IMG_FONT1_o},
{'O', CImgData::IMG_FONT1_O},

{'p', CImgData::IMG_FONT1_p},
{'P', CImgData::IMG_FONT1_P},

{'q', CImgData::IMG_FONT1_q},
{'Q', CImgData::IMG_FONT1_Q},

{'r', CImgData::IMG_FONT1_r},
{'R', CImgData::IMG_FONT1_R},

{'s', CImgData::IMG_FONT1_s},
{'S', CImgData::IMG_FONT1_S},

{'t', CImgData::IMG_FONT1_t},
{'T', CImgData::IMG_FONT1_T},

{'u', CImgData::IMG_FONT1_u},
{'U', CImgData::IMG_FONT1_U},

{'v', CImgData::IMG_FONT1_v},
{'V', CImgData::IMG_FONT1_V},

{'w', CImgData::IMG_FONT1_w},
{'W', CImgData::IMG_FONT1_W},

{'x', CImgData::IMG_FONT1_x},
{'X', CImgData::IMG_FONT1_X},

{'y', CImgData::IMG_FONT1_y},
{'Y', CImgData::IMG_FONT1_Y},

{'z', CImgData::IMG_FONT1_z},
{'Z', CImgData::IMG_FONT1_Z},

{'æ', CImgData::IMG_FONT1_ae},
{'Æ', CImgData::IMG_FONT1_AE},

{'ø', CImgData::IMG_FONT1_o_skreslone},
{'Ø', CImgData::IMG_FONT1_O_skreslone},

{'ą', CImgData::IMG_FONT1_a_ogonekDolP},
{'Ą', CImgData::IMG_FONT1_A_ogonekDolP},

{'ę', CImgData::IMG_FONT1_e_ogonekDolP},
{'Ę', CImgData::IMG_FONT1_E_ogonekDolP},

{'ć', CImgData::IMG_FONT1_c_ogonekGoraP},
{'Ć', CImgData::IMG_FONT1_C_ogonekGoraP},

{'ł', CImgData::IMG_FONT1_l_kreskaUkos},
{'Ł', CImgData::IMG_FONT1_L_kreskaUkos},

{'ń', CImgData::IMG_FONT1_n_ogonekGoraP},
{'Ń', CImgData::IMG_FONT1_N_ogonekGoraP},

{'ó', CImgData::IMG_FONT1_o_ogonekGoraP},
{'Ó', CImgData::IMG_FONT1_O_ogonekGoraP},

{'ś', CImgData::IMG_FONT1_s_ogonekGoraP},
{'Ś', CImgData::IMG_FONT1_S_ogonekGoraP},

{'ż', CImgData::IMG_FONT1_z_kropka},
{'Ż', CImgData::IMG_FONT1_Z_kropka},

{'ź', CImgData::IMG_FONT1_z_ogonekGoraP},
{'Ź', CImgData::IMG_FONT1_Z_ogonekGoraP},

{'á', CImgData::IMG_FONT1_a_ogonekGoraP},
{'Á', CImgData::IMG_FONT1_A_ogonekGoraP},

{'č', CImgData::IMG_FONT1_c_daszekDol},
{'Č', CImgData::IMG_FONT1_C_daszekDol},

{'ď', CImgData::IMG_FONT1_d_prim},
{'Ď', CImgData::IMG_FONT1_D_prim},

{'đ', CImgData::IMG_FONT1_d_kreslone},
{'Đ', CImgData::IMG_FONT1_D_kreslone},

{'é', CImgData::IMG_FONT1_e_ogonekGoraP},
{'É', CImgData::IMG_FONT1_E_ogonekGoraP},

{'ě', CImgData::IMG_FONT1_e_daszekDol},
{'Ě', CImgData::IMG_FONT1_E_daszekDol},

{'í', CImgData::IMG_FONT1_i_ogonekGoraP},
{'Í', CImgData::IMG_FONT1_I_ogonekGoraP},

{'ì', CImgData::IMG_FONT1_i_ogonekGoraL},
{'Ì', CImgData::IMG_FONT1_I_ogonekGoraL},

{'ĺ', CImgData::IMG_FONT1_l_ogonekGoraP},
{'Ĺ', CImgData::IMG_FONT1_L_ogonekGoraP},

{'ľ', CImgData::IMG_FONT1_l_prim},
{'Ľ', CImgData::IMG_FONT1_L_prim},

{'ň', CImgData::IMG_FONT1_n_daszekDol},
{'Ň', CImgData::IMG_FONT1_N_daszekDol},

{'ó', CImgData::IMG_FONT1_o_ogonekGoraP},
{'Ó', CImgData::IMG_FONT1_O_ogonekGoraP},

{'ô', CImgData::IMG_FONT1_o_daszekGora},
{'Ô', CImgData::IMG_FONT1_O_daszekGora},

{'ř', CImgData::IMG_FONT1_r_daszekDol},
{'Ř', CImgData::IMG_FONT1_R_daszekDol},

{'ŕ', CImgData::IMG_FONT1_r_ogonekGoraP},
{'Ŕ', CImgData::IMG_FONT1_R_ogonekGoraP},

{'š', CImgData::IMG_FONT1_s_daszekDol},
{'Š', CImgData::IMG_FONT1_S_daszekDol},

{'ș', CImgData::IMG_FONT1_s_ogonekDolL},
{'Ș', CImgData::IMG_FONT1_S_ogonekDolL},

{'ť', CImgData::IMG_FONT1_t_prim},
{'Ť', CImgData::IMG_FONT1_T_prim},

{'ț', CImgData::IMG_FONT1_t_ogonekDolL},
{'Ț', CImgData::IMG_FONT1_T_ogonekDolL},

{'ú', CImgData::IMG_FONT1_u_ogonekGoraP},
{'Ú', CImgData::IMG_FONT1_U_ogonekGoraP},

{'ů', CImgData::IMG_FONT1_u_kropka},
{'Ů', CImgData::IMG_FONT1_U_kropka},

{'ý', CImgData::IMG_FONT1_y_ogonekGoraP},
{'Ý', CImgData::IMG_FONT1_Y_ogonekGoraP},

{'ž', CImgData::IMG_FONT1_z_daszekDol},
{'Ž', CImgData::IMG_FONT1_Z_daszekDol},

{'ä', CImgData::IMG_FONT1_a_dwukropek},
{'Ä', CImgData::IMG_FONT1_A_dwukropek},

{'ö', CImgData::IMG_FONT1_o_dwukropek},
{'Ö', CImgData::IMG_FONT1_O_dwukropek},

{'ü', CImgData::IMG_FONT1_u_dwukropek},
{'Ü', CImgData::IMG_FONT1_U_dwukropek},

{'ß', CImgData::IMG_FONT1_SS},
{'ß', CImgData::IMG_FONT1_SS},

{'ñ', CImgData::IMG_FONT1_n_tylda},
{'Ñ', CImgData::IMG_FONT1_N_tylda},

{'é', CImgData::IMG_FONT1_e_ogonekGoraP},
{'É', CImgData::IMG_FONT1_E_ogonekGoraP},

{'ő', CImgData::IMG_FONT1_o_2ogonkiGoraP},
{'Ő', CImgData::IMG_FONT1_O_2ogonkiGoraP},

{'ű', CImgData::IMG_FONT1_u_2ogonkiGoraP},
{'Ű', CImgData::IMG_FONT1_U_2ogonkiGoraP},

{'à', CImgData::IMG_FONT1_a_ogonekGoraL},
{'À', CImgData::IMG_FONT1_A_ogonekGoraL},

{'â', CImgData::IMG_FONT1_a_daszekGora},
{'Â', CImgData::IMG_FONT1_A_daszekGora},

{'ă', CImgData::IMG_FONT1_a_daszekDol},
{'Ă', CImgData::IMG_FONT1_A_daszekDol},

{'ä', CImgData::IMG_FONT1_a_dwukropek},
{'Ä', CImgData::IMG_FONT1_A_dwukropek},

{'è', CImgData::IMG_FONT1_e_ogonekGoraL},
{'È', CImgData::IMG_FONT1_E_ogonekGoraL},

{'é', CImgData::IMG_FONT1_e_ogonekGoraP},
{'É', CImgData::IMG_FONT1_E_ogonekGoraP},

{'ê', CImgData::IMG_FONT1_e_daszekGora},
{'Ê', CImgData::IMG_FONT1_E_daszekGora},

{'ë', CImgData::IMG_FONT1_e_dwukropek},
{'Ë', CImgData::IMG_FONT1_E_dwukropek},

{'î', CImgData::IMG_FONT1_i_daszekGora},
{'Î', CImgData::IMG_FONT1_I_daszekGora},

{'ĭ', CImgData::IMG_FONT1_i_daszekDol},
{'Ĭ', CImgData::IMG_FONT1_I_daszekDol},

{'ï', CImgData::IMG_FONT1_i_dwukropek},
{'Ï', CImgData::IMG_FONT1_I_dwukropek},

{'ô', CImgData::IMG_FONT1_o_daszekGora},
{'Ô', CImgData::IMG_FONT1_O_daszekGora},

{'œ', CImgData::IMG_FONT1_oe},
{'Œ', CImgData::IMG_FONT1_OE},

/* {'õ', CImgData::IMG_FONT1_o_wezyk_gora}, */
/* {'Õ', CImgData::IMG_FONT1_O_wezyk_gora}, */

{'ē', CImgData::IMG_FONT1_e_kreska},
{'Ē', CImgData::IMG_FONT1_E_kreska},

/* {'ģ', CImgData::IMG_FONT1_g_kreska_skos_gora}, */
/* {'Ģ', CImgData::IMG_FONT1_G_kreska_skos_dol}, */

/* {'ī', CImgData::IMG_FONT1_i_kreska_gora}, */
/* {'Ī', CImgData::IMG_FONT1_I_kreska_gora}, */

/* {'ķ', CImgData::IMG_FONT1_k_kreska_skos_dol}, */
/* {'Ķ', CImgData::IMG_FONT1_K_kreska_skos_dol}, */

{'ļ', CImgData::IMG_FONT1_l_kreska_skos_dol},
{'Ļ', CImgData::IMG_FONT1_L_kreska_skos_dol},

/* {'ņ', CImgData::IMG_FONT1_n_kreska_skos_dol}, */
/* {'Ņ', CImgData::IMG_FONT1_N_kreska_skos_dol}, */

/* {'ū', CImgData::IMG_FONT1_u_kreska_gora}, */
/* {'Ū', CImgData::IMG_FONT1_U_kreska_gora}, */

/* {'ñ', CImgData::IMG_FONT1_n_wezyk_gora}, */
/* {'Ñ', CImgData::IMG_FONT1_N_wezyk_gora}, */

{'α', CImgData::IMG_FONT1_alfa},
{'Α', CImgData::IMG_FONT1_Alfa},

{'ά', CImgData::IMG_FONT1_alfa_kreska},
{'Ά', CImgData::IMG_FONT1_Alfa_kreska},

{'β', CImgData::IMG_FONT1_beta},
{'Β', CImgData::IMG_FONT1_Beta},

{'γ', CImgData::IMG_FONT1_gama},
{'Γ', CImgData::IMG_FONT1_Gama},

{'δ', CImgData::IMG_FONT1_delta},
{'Δ', CImgData::IMG_FONT1_Delta},

{'ε', CImgData::IMG_FONT1_epsilon},
{'Ε', CImgData::IMG_FONT1_Epsilon},

/* {'έ', CImgData::IMG_FONT1_epsilon_kreska}, */
/* {'Έ', CImgData::IMG_FONT1_Epsilon_kreska}, */

{'ζ', CImgData::IMG_FONT1_zeta},
{'Ζ', CImgData::IMG_FONT1_Zeta},

{'Η', CImgData::IMG_FONT1_Eta},
{'η', CImgData::IMG_FONT1_eta},

/* {'Θ', CImgData::IMG_FONT1_Teta}, */
/* {'θ', CImgData::IMG_FONT1_teta}, */

{'Ι', CImgData::IMG_FONT1_Jota},
{'ι', CImgData::IMG_FONT1_jota},

{'Κ', CImgData::IMG_FONT1_Kappa},
{'κ', CImgData::IMG_FONT1_kappa},

{'Λ', CImgData::IMG_FONT1_Lambda},
{'λ', CImgData::IMG_FONT1_lambda},

{'μ', CImgData::IMG_FONT1_mi},
{'Μ', CImgData::IMG_FONT1_Mi},

{'ν', CImgData::IMG_FONT1_ni},
{'Ν', CImgData::IMG_FONT1_Ni},

{'ξ', CImgData::IMG_FONT1_ksi},
{'Ξ', CImgData::IMG_FONT1_Ksi},

{'ο', CImgData::IMG_FONT1_omikron},
{'Ο', CImgData::IMG_FONT1_Omikron},

{'ό', CImgData::IMG_FONT1_omikron_kreska},
{'Ό', CImgData::IMG_FONT1_Omikron_kreska},

{'π', CImgData::IMG_FONT1_pi},
{'Π', CImgData::IMG_FONT1_Pi},

{'ρ', CImgData::IMG_FONT1_ro},
{'Ρ', CImgData::IMG_FONT1_Ro},

{'σ', CImgData::IMG_FONT1_sigma},
/* {'ς', CImgData::IMG_FONT1_sigma_koniec_wyrazu}, */
{'Σ', CImgData::IMG_FONT1_Sigma},

{'τ', CImgData::IMG_FONT1_tau},
{'Τ', CImgData::IMG_FONT1_Tau},

{'υ', CImgData::IMG_FONT1_ypsilon},
{'Υ', CImgData::IMG_FONT1_Ypsilon},

/* {'ύ', CImgData::IMG_FONT1_ypsilon_kreska}, */
/* {'Ύ', CImgData::IMG_FONT1_Ypsilon_kreska}, */

{'φ', CImgData::IMG_FONT1_fi},
{'Φ', CImgData::IMG_FONT1_Fi},

/* {'χ', CImgData::IMG_FONT1_chi}, */
/* {'Χ', CImgData::IMG_FONT1_Chi}, */

{'ψ', CImgData::IMG_FONT1_psi},
{'Ψ', CImgData::IMG_FONT1_Psi},

{'ω', CImgData::IMG_FONT1_omega},
{'Ω', CImgData::IMG_FONT1_Omega},

{'ù', CImgData::IMG_FONT1_u_ogonekGoraL},
{'Ù', CImgData::IMG_FONT1_U_ogonekGoraL},

{'û', CImgData::IMG_FONT1_u_daszekGora},
{'Û', CImgData::IMG_FONT1_U_daszekGora},

/* {'ŭ', CImgData::IMG_FONT1_u_daszekDol}, */
/* {'Ŭ', CImgData::IMG_FONT1_U_daszekDol}, */

{'ü', CImgData::IMG_FONT1_u_dwukropek},
{'Ü', CImgData::IMG_FONT1_U_dwukropek},

{'ÿ', CImgData::IMG_FONT1_y_dwukropek},
{'Ÿ', CImgData::IMG_FONT1_Y_dwukropek},

{'ç', CImgData::IMG_FONT1_c_ogonekDolL},
{'Ç', CImgData::IMG_FONT1_C_ogonekDolL},

/*---------- */

{'ė', CImgData::IMG_FONT1_e_kropka},
{'Ė', CImgData::IMG_FONT1_E_kropka},

{'į', CImgData::IMG_FONT1_i_ogonekDolP},
{'Į', CImgData::IMG_FONT1_I_ogonekDolP},

{'ų', CImgData::IMG_FONT1_u_haczykDolP},
{'Ų', CImgData::IMG_FONT1_U_haczykDolP},

{'ū', CImgData::IMG_FONT1_u_kreska},
{'Ū', CImgData::IMG_FONT1_U_kreska},

/* {'å', CImgData::IMG_FONT1_a_kolko_gora}, */
/* {'Å', CImgData::IMG_FONT1_A_kolko_gora}, */

{'а', CImgData::IMG_FONT1CYR_a},
{'А', CImgData::IMG_FONT1CYR_A},

{'б', CImgData::IMG_FONT1CYR_be},
{'Б', CImgData::IMG_FONT1CYR_BE},

{'в', CImgData::IMG_FONT1CYR_we},
{'В', CImgData::IMG_FONT1CYR_WE},

{'г', CImgData::IMG_FONT1CYR_gie},
{'Г', CImgData::IMG_FONT1CYR_GIE},

{'ґ', CImgData::IMG_FONT1CYR_ge},
{'Ґ', CImgData::IMG_FONT1CYR_GE},

{'д', CImgData::IMG_FONT1CYR_de},
{'Д', CImgData::IMG_FONT1CYR_DE},

{'е', CImgData::IMG_FONT1CYR_je},
{'Е', CImgData::IMG_FONT1CYR_JE},

{'є', CImgData::IMG_FONT1CYR_je_ukr},
{'Є', CImgData::IMG_FONT1CYR_JE_ukr},

{'ё', CImgData::IMG_FONT1CYR_jo},
{'Ё', CImgData::IMG_FONT1CYR_JO},

{'ј', CImgData::IMG_FONT1_j},
{'Ј', CImgData::IMG_FONT1_J},

{'ж', CImgData::IMG_FONT1CYR_z_kropka},
{'Ж', CImgData::IMG_FONT1CYR_Z_kropka},

{'з', CImgData::IMG_FONT1CYR_ze},
{'З', CImgData::IMG_FONT1CYR_ZE},

{'и', CImgData::IMG_FONT1CYR_i},
{'И', CImgData::IMG_FONT1CYR_I},

{'і', CImgData::IMG_FONT1CYR_i_ukr},
{'І', CImgData::IMG_FONT1CYR_I_ukr},

{'ї', CImgData::IMG_FONT1CYR_ji1},
{'Ї', CImgData::IMG_FONT1CYR_JI1},

{'й', CImgData::IMG_FONT1CYR_i_krotkie},
{'Й', CImgData::IMG_FONT1CYR_I_krotkie},

{'к', CImgData::IMG_FONT1CYR_ka},
{'К', CImgData::IMG_FONT1CYR_KA},

{'л', CImgData::IMG_FONT1CYR_el},
{'Л', CImgData::IMG_FONT1CYR_EL},

{'м', CImgData::IMG_FONT1CYR_em},
{'М', CImgData::IMG_FONT1CYR_EM},

{'н', CImgData::IMG_FONT1CYR_en},
{'Н', CImgData::IMG_FONT1CYR_EN},

{'о', CImgData::IMG_FONT1CYR_o},
{'О', CImgData::IMG_FONT1CYR_O},

{'п', CImgData::IMG_FONT1CYR_pe},
{'П', CImgData::IMG_FONT1CYR_PE},

{'р', CImgData::IMG_FONT1CYR_er},
{'Р', CImgData::IMG_FONT1CYR_ER},

{'с', CImgData::IMG_FONT1CYR_es},
{'С', CImgData::IMG_FONT1CYR_ES},

{'т', CImgData::IMG_FONT1CYR_te},
{'Т', CImgData::IMG_FONT1CYR_TE},

{'у', CImgData::IMG_FONT1CYR_u},
{'У', CImgData::IMG_FONT1CYR_U},

{'ф', CImgData::IMG_FONT1CYR_ef},
{'Ф', CImgData::IMG_FONT1CYR_EF},

{'х', CImgData::IMG_FONT1CYR_cha},
{'Х', CImgData::IMG_FONT1CYR_CHA},

{'ц', CImgData::IMG_FONT1CYR_ce},
{'Ц', CImgData::IMG_FONT1CYR_CE},

{'ч', CImgData::IMG_FONT1CYR_cze},
{'Ч', CImgData::IMG_FONT1CYR_CZE},

{'ш', CImgData::IMG_FONT1CYR_sza},
{'Ш', CImgData::IMG_FONT1CYR_SZA},

{'щ', CImgData::IMG_FONT1CYR_szcza},
{'Щ', CImgData::IMG_FONT1CYR_SZCZA},

{'ъ', CImgData::IMG_FONT1CYR_jor},
{'Ъ', CImgData::IMG_FONT1CYR_JOR},

{'ы', CImgData::IMG_FONT1CYR_jery},
{'Ы', CImgData::IMG_FONT1CYR_JERY},

{'ь', CImgData::IMG_FONT1CYR_jer},
{'Ь', CImgData::IMG_FONT1CYR_JER},

{'э', CImgData::IMG_FONT1CYR_e},
{'Э', CImgData::IMG_FONT1CYR_E},

{'ю', CImgData::IMG_FONT1CYR_ju},
{'Ю', CImgData::IMG_FONT1CYR_JU},

{'я', CImgData::IMG_FONT1CYR_ja},
{'Я', CImgData::IMG_FONT1CYR_JA}, };

const CGraphicFont::TImgCharMap CFont::CHAR_MAP_FONT_2[] =
{
{'°', CImgData::IMG_FONT2_ST_CELCIUSZ},
{' ', CImgData::IMG_FONT2_SPACJA},
{'%', CImgData::IMG_FONT2_PROCENT},
{'+', CImgData::IMG_FONT2_PLUS},
{',', CImgData::IMG_FONT2_PRZECINEK},
{'-', CImgData::IMG_FONT2_MINUS},
{'.', CImgData::IMG_FONT2_KROPKA},
{':', CImgData::IMG_FONT2_DWUKROPEK},
{'/', CImgData::IMG_FONT2_SLASH},
{'\\', CImgData::IMG_FONT2_BACKSLASH},
{'¿', CImgData::IMG_FONT2_PYTAJNIK_OBROCONY},
{'[', CImgData::IMG_FONT2_NAWIAS_PROSTOK_LEWY},
{']', CImgData::IMG_FONT2_NAWIAS_PROSTOK_PRAWY},

{'0', CImgData::IMG_FONT2_0},
{'1', CImgData::IMG_FONT2_1},
{'2', CImgData::IMG_FONT2_2},
{'3', CImgData::IMG_FONT2_3},
{'4', CImgData::IMG_FONT2_4},
{'5', CImgData::IMG_FONT2_5},
{'6', CImgData::IMG_FONT2_6},
{'7', CImgData::IMG_FONT2_7},
{'8', CImgData::IMG_FONT2_8},
{'9', CImgData::IMG_FONT2_9},

{'a', CImgData::IMG_FONT2_A},
{'A', CImgData::IMG_FONT2_A},

{'b', CImgData::IMG_FONT2_B},
{'B', CImgData::IMG_FONT2_B},

{'c', CImgData::IMG_FONT2_C},
{'C', CImgData::IMG_FONT2_C},

{'d', CImgData::IMG_FONT2_D},
{'D', CImgData::IMG_FONT2_D},

{'e', CImgData::IMG_FONT2_E},
{'E', CImgData::IMG_FONT2_E},

{'f', CImgData::IMG_FONT2_F},
{'F', CImgData::IMG_FONT2_F},

{'g', CImgData::IMG_FONT2_G},
{'G', CImgData::IMG_FONT2_G},

{'h', CImgData::IMG_FONT2_H},
{'H', CImgData::IMG_FONT2_H},

{'i', CImgData::IMG_FONT2_I},
{'I', CImgData::IMG_FONT2_I},

{'j', CImgData::IMG_FONT2_J},
{'J', CImgData::IMG_FONT2_J},

{'k', CImgData::IMG_FONT2_K},
{'K', CImgData::IMG_FONT2_K},

{'l', CImgData::IMG_FONT2_L},
{'L', CImgData::IMG_FONT2_L},

{'m', CImgData::IMG_FONT2_M},
{'M', CImgData::IMG_FONT2_M},

{'n', CImgData::IMG_FONT2_N},
{'N', CImgData::IMG_FONT2_N},

{'o', CImgData::IMG_FONT2_O},
{'O', CImgData::IMG_FONT2_O},

{'p', CImgData::IMG_FONT2_P},
{'P', CImgData::IMG_FONT2_P},

{'q', CImgData::IMG_FONT2_Q},
{'Q', CImgData::IMG_FONT2_Q},

{'r', CImgData::IMG_FONT2_R},
{'R', CImgData::IMG_FONT2_R},

{'s', CImgData::IMG_FONT2_S},
{'S', CImgData::IMG_FONT2_S},

{'t', CImgData::IMG_FONT2_T},
{'T', CImgData::IMG_FONT2_T},

{'u', CImgData::IMG_FONT2_U},
{'U', CImgData::IMG_FONT2_U},

{'v', CImgData::IMG_FONT2_V},
{'V', CImgData::IMG_FONT2_V},

{'w', CImgData::IMG_FONT2_W},
{'W', CImgData::IMG_FONT2_W},

{'x', CImgData::IMG_FONT2_X},
{'X', CImgData::IMG_FONT2_X},

{'y', CImgData::IMG_FONT2_Y},
{'Y', CImgData::IMG_FONT2_Y},

{'z', CImgData::IMG_FONT2_Z},
{'Z', CImgData::IMG_FONT2_Z},

{'æ', CImgData::IMG_FONT2_AE},
{'Æ', CImgData::IMG_FONT2_AE},

{'ø', CImgData::IMG_FONT2_O_skreslone},
{'Ø', CImgData::IMG_FONT2_O_skreslone},

{'ą', CImgData::IMG_FONT2_A_ogonekDolP},
{'Ą', CImgData::IMG_FONT2_A_ogonekDolP},

{'ę', CImgData::IMG_FONT2_E_ogonekDolP},
{'Ę', CImgData::IMG_FONT2_E_ogonekDolP},

{'ć', CImgData::IMG_FONT2_C_ogonekGoraP},
{'Ć', CImgData::IMG_FONT2_C_ogonekGoraP},

{'ł', CImgData::IMG_FONT2_L_kreskaUkos},
{'Ł', CImgData::IMG_FONT2_L_kreskaUkos},

{'ń', CImgData::IMG_FONT2_N_ogonekGoraP},
{'Ń', CImgData::IMG_FONT2_N_ogonekGoraP},

{'ó', CImgData::IMG_FONT2_O_ogonekGoraP},
{'Ó', CImgData::IMG_FONT2_O_ogonekGoraP},

{'ś', CImgData::IMG_FONT2_S_ogonekGoraP},
{'Ś', CImgData::IMG_FONT2_S_ogonekGoraP},

{'ż', CImgData::IMG_FONT2_Z_kropka},
{'Ż', CImgData::IMG_FONT2_Z_kropka},

{'ź', CImgData::IMG_FONT2_Z_ogonekGoraP},
{'Ź', CImgData::IMG_FONT2_Z_ogonekGoraP},

{'á', CImgData::IMG_FONT2_A_ogonekGoraP},
{'Á', CImgData::IMG_FONT2_A_ogonekGoraP},

{'č', CImgData::IMG_FONT2_C_daszekDol},
{'Č', CImgData::IMG_FONT2_C_daszekDol},

{'ď', CImgData::IMG_FONT2_D_prim},
{'Ď', CImgData::IMG_FONT2_D_prim},

{'đ', CImgData::IMG_FONT2_D_kreslone},
{'Đ', CImgData::IMG_FONT2_D_kreslone},

{'é', CImgData::IMG_FONT2_E_ogonekGoraP},
{'É', CImgData::IMG_FONT2_E_ogonekGoraP},

{'ě', CImgData::IMG_FONT2_E_daszekDol},
{'Ě', CImgData::IMG_FONT2_E_daszekDol},

{'í', CImgData::IMG_FONT2_I_ogonekGoraP},
{'Í', CImgData::IMG_FONT2_I_ogonekGoraP},

{'ĺ', CImgData::IMG_FONT2_L_ogonekGoraP},
{'Ĺ', CImgData::IMG_FONT2_L_ogonekGoraP},

{'ľ', CImgData::IMG_FONT2_L_prim},
{'Ľ', CImgData::IMG_FONT2_L_prim},

{'ň', CImgData::IMG_FONT2_N_daszekDol},
{'Ň', CImgData::IMG_FONT2_N_daszekDol},

{'ó', CImgData::IMG_FONT2_O_ogonekGoraP},
{'Ó', CImgData::IMG_FONT2_O_ogonekGoraP},

{'ô', CImgData::IMG_FONT2_O_daszekGora},
{'Ô', CImgData::IMG_FONT2_O_daszekGora},

{'ř', CImgData::IMG_FONT2_R_daszekDol},
{'Ř', CImgData::IMG_FONT2_R_daszekDol},

{'š', CImgData::IMG_FONT2_S_daszekDol},
{'Š', CImgData::IMG_FONT2_S_daszekDol},

{'ť', CImgData::IMG_FONT2_T_prim},
{'Ť', CImgData::IMG_FONT2_T_prim},

{'ú', CImgData::IMG_FONT2_U_ogonekGoraP},
{'Ú', CImgData::IMG_FONT2_U_ogonekGoraP},

{'ů', CImgData::IMG_FONT2_U_kropka},
{'Ů', CImgData::IMG_FONT2_U_kropka},

{'ý', CImgData::IMG_FONT2_Y_ogonekGoraP},
{'Ý', CImgData::IMG_FONT2_Y_ogonekGoraP},

{'ž', CImgData::IMG_FONT2_Z_daszekDol},
{'Ž', CImgData::IMG_FONT2_Z_daszekDol},

{'ä', CImgData::IMG_FONT2_A_dwukropek},
{'Ä', CImgData::IMG_FONT2_A_dwukropek},

{'ö', CImgData::IMG_FONT2_O_dwukropek},
{'Ö', CImgData::IMG_FONT2_O_dwukropek},

{'ü', CImgData::IMG_FONT2_U_dwukropek},
{'Ü', CImgData::IMG_FONT2_U_dwukropek},

{'ß', CImgData::IMG_FONT2_SS},
{'ß', CImgData::IMG_FONT2_SS},

{'ñ', CImgData::IMG_FONT2_N_tylda},
{'Ñ', CImgData::IMG_FONT2_N_tylda},

{'é', CImgData::IMG_FONT2_E_ogonekGoraP},
{'É', CImgData::IMG_FONT2_E_ogonekGoraP},

{'ő', CImgData::IMG_FONT2_O_2ogonkiGoraP},
{'Ő', CImgData::IMG_FONT2_O_2ogonkiGoraP},

{'ű', CImgData::IMG_FONT2_U_2ogonkiGoraP},
{'Ű', CImgData::IMG_FONT2_U_2ogonkiGoraP},

{'à', CImgData::IMG_FONT2_A_ogonekGoraL},
{'À', CImgData::IMG_FONT2_A_ogonekGoraL},

{'â', CImgData::IMG_FONT2_A_daszekGora},
{'Â', CImgData::IMG_FONT2_A_daszekGora},

{'ä', CImgData::IMG_FONT2_A_dwukropek},
{'Ä', CImgData::IMG_FONT2_A_dwukropek},

{'è', CImgData::IMG_FONT2_E_ogonekGoraL},
{'È', CImgData::IMG_FONT2_E_ogonekGoraL},

{'é', CImgData::IMG_FONT2_E_ogonekGoraP},
{'É', CImgData::IMG_FONT2_E_ogonekGoraP},

{'ê', CImgData::IMG_FONT2_E_daszekGora},
{'Ê', CImgData::IMG_FONT2_E_daszekGora},

{'ë', CImgData::IMG_FONT2_E_dwukropek},
{'Ë', CImgData::IMG_FONT2_E_dwukropek},

{'î', CImgData::IMG_FONT2_I_daszekGora},
{'Î', CImgData::IMG_FONT2_I_daszekGora},

{'ï', CImgData::IMG_FONT2_I_dwukropek},
{'Ï', CImgData::IMG_FONT2_I_dwukropek},

{'ô', CImgData::IMG_FONT2_O_daszekGora},
{'Ô', CImgData::IMG_FONT2_O_daszekGora},

{'œ', CImgData::IMG_FONT2_OE},
{'Œ', CImgData::IMG_FONT2_OE},

/* {'õ',CImgData::IMG_FONT2_O_wezyk_gora}, */
/* {'Õ',CImgData::IMG_FONT2_O_wezyk_gora}, */

{'ā', CImgData::IMG_FONT1_a_kreska},
{'Ā', CImgData::IMG_FONT1_a_kreska},

/* {'ē', CImgData::IMG_FONT2_E_kreska_gora}, */
/* {'Ē',CImgData::IMG_FONT2_E_kreska_gora}, */

/* {'ģ',CImgData::IMG_FONT2_G_kreska_skos_dol}, */
/* {'Ģ',CImgData::IMG_FONT2_G_kreska_skos_dol}, */

/* {'ī',CImgData::IMG_FONT2_I_kreska_gora}, */
/* {'Ī',CImgData::IMG_FONT2_I_kreska_gora}, */

/* {'ķ',CImgData::IMG_FONT2_K_kreska_skos_dol}, */
/* {'Ķ',CImgData::IMG_FONT2_K_kreska_skos_dol}, */

/* {'ļ',CImgData::IMG_FONT2_L_kreska_skos_dol}, */
/* {'Ļ',CImgData::IMG_FONT2_L_kreska_skos_dol}, */

/* {'ņ',CImgData::IMG_FONT2_N_kreska_skos_dol}, */
/* {'Ņ',CImgData::IMG_FONT2_N_kreska_skos_dol}, */

/* {'ū',CImgData::IMG_FONT2_U_kreska_gora}, */
/* {'Ū',CImgData::IMG_FONT2_U_kreska_gora}, */

/* {'ñ',CImgData::IMG_FONT2_N_wezyk_gora}, */
/* {'Ñ',CImgData::IMG_FONT2_N_wezyk_gora}, */

{'α', CImgData::IMG_FONT2_Alfa},
{'Α', CImgData::IMG_FONT2_Alfa},

{'β', CImgData::IMG_FONT2_Beta},
{'Β', CImgData::IMG_FONT2_Beta},

{'γ', CImgData::IMG_FONT2_Gamma},
{'Γ', CImgData::IMG_FONT2_Gamma},

{'δ', CImgData::IMG_FONT2_Delta},
{'Δ', CImgData::IMG_FONT2_Delta},

{'ε', CImgData::IMG_FONT2_Epsilon},
{'Ε', CImgData::IMG_FONT2_Epsilon},

{'ζ', CImgData::IMG_FONT2_Zeta},
{'Ζ', CImgData::IMG_FONT2_Zeta},

{'η', CImgData::IMG_FONT2_Eta},
{'Η', CImgData::IMG_FONT2_Eta},

{'Θ', CImgData::IMG_FONT2_Teta},
{'θ', CImgData::IMG_FONT2_Teta},

{'Ι', CImgData::IMG_FONT2_Jota},
{'ι', CImgData::IMG_FONT2_Jota},

{'Κ', CImgData::IMG_FONT2_Kappa},
{'κ', CImgData::IMG_FONT2_Kappa},

{'Λ', CImgData::IMG_FONT2_Lambda},
{'λ', CImgData::IMG_FONT2_Lambda},

{'μ', CImgData::IMG_FONT2_Mi},
{'Μ', CImgData::IMG_FONT2_Mi},

{'ν', CImgData::IMG_FONT2_Ni},
{'Ν', CImgData::IMG_FONT2_Ni},

{'ξ', CImgData::IMG_FONT2_Ksi},
{'Ξ', CImgData::IMG_FONT2_Ksi},

{'ο', CImgData::IMG_FONT2_Omikron},
{'Ο', CImgData::IMG_FONT2_Omikron},

{'π', CImgData::IMG_FONT2_Pi},
{'Π', CImgData::IMG_FONT2_Pi},

{'ρ', CImgData::IMG_FONT2_Ro},
{'Ρ', CImgData::IMG_FONT2_Ro},

{'σ', CImgData::IMG_FONT2_Sigma},
{'ς', CImgData::IMG_FONT2_Sigma},
{'Σ', CImgData::IMG_FONT2_Sigma},

{'τ', CImgData::IMG_FONT2_Tau},
{'Τ', CImgData::IMG_FONT2_Tau},

{'υ', CImgData::IMG_FONT2_Ypsilon},
{'Υ', CImgData::IMG_FONT2_Ypsilon},

{'φ', CImgData::IMG_FONT2_Fi},
{'Φ', CImgData::IMG_FONT2_Fi},

{'χ', CImgData::IMG_FONT2_Chi},
{'Χ', CImgData::IMG_FONT2_Chi},

{'ψ', CImgData::IMG_FONT2_Psi},
{'Ψ', CImgData::IMG_FONT2_Psi},

/*{'ω',CImgData::IMG_FONT2_Omega}, */
/*{'Ω',CImgData::IMG_FONT2_Omega}, */

{'ù', CImgData::IMG_FONT2_U_ogonekGoraL},
{'Ù', CImgData::IMG_FONT2_U_ogonekGoraL},

{'û', CImgData::IMG_FONT2_U_daszekGora},
{'Û', CImgData::IMG_FONT2_U_daszekGora},

{'ü', CImgData::IMG_FONT2_U_dwukropek},
{'Ü', CImgData::IMG_FONT2_U_dwukropek},

{'ÿ', CImgData::IMG_FONT2_Y_dwukropek},
{'Ÿ', CImgData::IMG_FONT2_Y_dwukropek},

{'ç', CImgData::IMG_FONT2_C_ogonekDolL},
{'Ç', CImgData::IMG_FONT2_C_ogonekDolL},

{'ė', CImgData::IMG_FONT2_E_kropka},
{'Ė', CImgData::IMG_FONT2_E_kropka},

{'į', CImgData::IMG_FONT2_I_ogonekDolP},
{'Į', CImgData::IMG_FONT2_I_ogonekDolP},

{'ų', CImgData::IMG_FONT2_U_haczykDolP},
{'Ų', CImgData::IMG_FONT2_U_haczykDolP},

{'ū', CImgData::IMG_FONT2_U_kreska},
{'Ū', CImgData::IMG_FONT2_U_kreska},

{'å', CImgData::IMG_FONT2_A_kropka},
{'Å', CImgData::IMG_FONT2_A_kropka},

{'а', CImgData::IMG_FONT2CYR_A},
{'А', CImgData::IMG_FONT2CYR_A},

{'б', CImgData::IMG_FONT2CYR_BE},
{'Б', CImgData::IMG_FONT2CYR_BE},

{'в', CImgData::IMG_FONT2CYR_WE},
{'В', CImgData::IMG_FONT2CYR_WE},

{'г', CImgData::IMG_FONT2CYR_GIE},
{'Г', CImgData::IMG_FONT2CYR_GIE},

{'ґ', CImgData::IMG_FONT2CYR_GE},
{'Ґ', CImgData::IMG_FONT2CYR_GE},

{'д', CImgData::IMG_FONT2CYR_DE},
{'Д', CImgData::IMG_FONT2CYR_DE},

{'е', CImgData::IMG_FONT2CYR_JE},
{'Е', CImgData::IMG_FONT2CYR_JE},

{'є', CImgData::IMG_FONT2CYR_JE_ukr},
{'Є', CImgData::IMG_FONT2CYR_JE_ukr},

{'ё', CImgData::IMG_FONT2CYR_JO},
{'Ё', CImgData::IMG_FONT2CYR_JO},

{'ж', CImgData::IMG_FONT2CYR_Z_kropka},
{'Ж', CImgData::IMG_FONT2CYR_Z_kropka},

{'з', CImgData::IMG_FONT2CYR_ZE},
{'З', CImgData::IMG_FONT2CYR_ZE},

{'и', CImgData::IMG_FONT2CYR_I},
{'И', CImgData::IMG_FONT2CYR_I},

{'і', CImgData::IMG_FONT2CYR_I_ukr},
{'І', CImgData::IMG_FONT2CYR_I_ukr},

{'ї', CImgData::IMG_FONT2CYR_JI1},
{'Ї', CImgData::IMG_FONT2CYR_JI1},

{'й', CImgData::IMG_FONT2CYR_I_krotkie},
{'Й', CImgData::IMG_FONT2CYR_I_krotkie},

{'к', CImgData::IMG_FONT2CYR_KA},
{'К', CImgData::IMG_FONT2CYR_KA},

{'л', CImgData::IMG_FONT2CYR_EL},
{'Л', CImgData::IMG_FONT2CYR_EL},

{'м', CImgData::IMG_FONT2CYR_EM},
{'М', CImgData::IMG_FONT2CYR_EM},

{'н', CImgData::IMG_FONT2CYR_EN},
{'Н', CImgData::IMG_FONT2CYR_EN},

{'о', CImgData::IMG_FONT2CYR_O},
{'О', CImgData::IMG_FONT2CYR_O},

{'п', CImgData::IMG_FONT2CYR_PE},
{'П', CImgData::IMG_FONT2CYR_PE},

{'р', CImgData::IMG_FONT2CYR_ER},
{'Р', CImgData::IMG_FONT2CYR_ER},

{'с', CImgData::IMG_FONT2CYR_ES},
{'С', CImgData::IMG_FONT2CYR_ES},

{'т', CImgData::IMG_FONT2CYR_TE},
{'Т', CImgData::IMG_FONT2CYR_TE},

{'у', CImgData::IMG_FONT2CYR_U},
{'У', CImgData::IMG_FONT2CYR_U},

{'ф', CImgData::IMG_FONT2CYR_EF},
{'Ф', CImgData::IMG_FONT2CYR_EF},

{'х', CImgData::IMG_FONT2CYR_CHA},
{'Х', CImgData::IMG_FONT2CYR_CHA},

{'ц', CImgData::IMG_FONT2CYR_CE},
{'Ц', CImgData::IMG_FONT2CYR_CE},

{'ч', CImgData::IMG_FONT2CYR_CZE},
{'Ч', CImgData::IMG_FONT2CYR_CZE},

{'ш', CImgData::IMG_FONT2CYR_SZA},
{'Ш', CImgData::IMG_FONT2CYR_SZA},

{'щ', CImgData::IMG_FONT2CYR_SZCZA},
{'Щ', CImgData::IMG_FONT2CYR_SZCZA},

{'ъ', CImgData::IMG_FONT2CYR_JOR},
{'Ъ', CImgData::IMG_FONT2CYR_JOR},

{'ы', CImgData::IMG_FONT2CYR_JERY},
{'Ы', CImgData::IMG_FONT2CYR_JERY},

{'ь', CImgData::IMG_FONT2CYR_JER},
{'Ь', CImgData::IMG_FONT2CYR_JER},

{'э', CImgData::IMG_FONT2CYR_E},
{'Э', CImgData::IMG_FONT2CYR_E},

{'ю', CImgData::IMG_FONT2CYR_JU},
{'Ю', CImgData::IMG_FONT2CYR_JU},

{'я', CImgData::IMG_FONT2CYR_JA},
{'Я', CImgData::IMG_FONT2CYR_JA}, };

const CGraphicFont::TImgCharMap CFont::CHAR_MAP_FONT_3[] =
{
{'0', CImgData::IMG_FONT3_0},
{'1', CImgData::IMG_FONT3_1},
{'2', CImgData::IMG_FONT3_2},
{'3', CImgData::IMG_FONT3_3},
{'4', CImgData::IMG_FONT3_4},
{'5', CImgData::IMG_FONT3_5},
{'6', CImgData::IMG_FONT3_6},
{'7', CImgData::IMG_FONT3_7},
{'8', CImgData::IMG_FONT3_8},
{'9', CImgData::IMG_FONT3_9},
{':', CImgData::IMG_FONT3_DWUKROPEK},
{'+', CImgData::IMG_FONT3_PLUS},
{'-', CImgData::IMG_FONT3_MINUS},
{'%', CImgData::IMG_FONT3_PROCENT},
{'.', CImgData::IMG_FONT3_KROPKA},
{' ', CImgData::IMG_FONT3_SPACJA}, };

const CGraphicFont::TImgCharMap CFont::CHAR_MAP_FONT_4[] =
{
{'0', CImgData::IMG_FONT4_0},
{'1', CImgData::IMG_FONT4_1},
{'2', CImgData::IMG_FONT4_2},
{'3', CImgData::IMG_FONT4_3},
{'4', CImgData::IMG_FONT4_4},
{'5', CImgData::IMG_FONT4_5},
{'6', CImgData::IMG_FONT4_6},
{'7', CImgData::IMG_FONT4_7},
{'8', CImgData::IMG_FONT4_8},
{'9', CImgData::IMG_FONT4_9},
{'°', CImgData::IMG_FONT4_ST_CELCIUSZ},
{':', CImgData::IMG_FONT4_DWUKROPEK},
{'+', CImgData::IMG_FONT4_PLUS},
{'-', CImgData::IMG_FONT4_MINUS},
{'%', CImgData::IMG_FONT4_PROCENT},
{'A', CImgData::IMG_FONT4_A},
{'B', CImgData::IMG_FONT4_B},
{'C', CImgData::IMG_FONT4_C},
{'D', CImgData::IMG_FONT4_D},
{'E', CImgData::IMG_FONT4_E},
{'F', CImgData::IMG_FONT4_F},
{'.', CImgData::IMG_FONT4_KROPKA},
{' ', CImgData::IMG_FONT4_SPACJA}, };

const CGraphicFont::TImgCharMap CFont::CHAR_MAP_FONT_5[] =
{
{'0', CImgData::IMG_FONT5_0},
{'1', CImgData::IMG_FONT5_1},
{'2', CImgData::IMG_FONT5_2},
{'3', CImgData::IMG_FONT5_3},
{'4', CImgData::IMG_FONT5_4},
{'5', CImgData::IMG_FONT5_5},
{'6', CImgData::IMG_FONT5_6},
{'7', CImgData::IMG_FONT5_7},
{'8', CImgData::IMG_FONT5_8},
{'9', CImgData::IMG_FONT5_9},
{'.', CImgData::IMG_FONT5_KROPKA},
{'-', CImgData::IMG_FONT5_KRESKA}, };

const CGraphicFont::TImgCharMap CFont::CHAR_MAP_FONT_ASCII[] =
{
{' ', CImgData::IMG_FONT_ASCII_SPACJA},
{'!', CImgData::IMG_FONT_ASCII_WYKRZYKNIK},
{'"', CImgData::IMG_FONT_ASCII_CUDZYSLOW},
{'#', CImgData::IMG_FONT_ASCII_HASZ},
{'$', CImgData::IMG_FONT_ASCII_DOLAR},
{'%', CImgData::IMG_FONT_ASCII_PROCENT},
{'&', CImgData::IMG_FONT_ASCII_AMPERSAND},
{'\'', CImgData::IMG_FONT_ASCII_APOSTROF},
{'(', CImgData::IMG_FONT_ASCII_NAWIAS_OKRAGLY_LEWY},
{')', CImgData::IMG_FONT_ASCII_NAWIAS_OKRAGLY_PRAWY},
{'*', CImgData::IMG_FONT_ASCII_GWIAZDKA},
{'+', CImgData::IMG_FONT_ASCII_PLUS},
{',', CImgData::IMG_FONT_ASCII_PRZECINEK},
{'-', CImgData::IMG_FONT_ASCII_MINUS},
{'.', CImgData::IMG_FONT_ASCII_KROPKA},
{'/', CImgData::IMG_FONT_ASCII_SLASH},
{'0', CImgData::IMG_FONT_ASCII_0},
{'1', CImgData::IMG_FONT_ASCII_1},
{'2', CImgData::IMG_FONT_ASCII_2},
{'3', CImgData::IMG_FONT_ASCII_3},
{'4', CImgData::IMG_FONT_ASCII_4},
{'5', CImgData::IMG_FONT_ASCII_5},
{'6', CImgData::IMG_FONT_ASCII_6},
{'7', CImgData::IMG_FONT_ASCII_7},
{'8', CImgData::IMG_FONT_ASCII_8},
{'9', CImgData::IMG_FONT_ASCII_9},
{':', CImgData::IMG_FONT_ASCII_DWUKROPEK},
{';', CImgData::IMG_FONT_ASCII_SREDNIK},
{'<', CImgData::IMG_FONT_ASCII_MNIEJSZY},
{'=', CImgData::IMG_FONT_ASCII_ROWNY},
{'>', CImgData::IMG_FONT_ASCII_WIEKSZY},
{'?', CImgData::IMG_FONT_ASCII_PYTAJNIK},
{'@', CImgData::IMG_FONT_ASCII_MALPA},
{'A', CImgData::IMG_FONT_ASCII_A},
{'B', CImgData::IMG_FONT_ASCII_B},
{'C', CImgData::IMG_FONT_ASCII_C},
{'D', CImgData::IMG_FONT_ASCII_D},
{'E', CImgData::IMG_FONT_ASCII_E},
{'F', CImgData::IMG_FONT_ASCII_F},
{'G', CImgData::IMG_FONT_ASCII_G},
{'H', CImgData::IMG_FONT_ASCII_H},
{'I', CImgData::IMG_FONT_ASCII_I},
{'J', CImgData::IMG_FONT_ASCII_J},
{'K', CImgData::IMG_FONT_ASCII_K},
{'L', CImgData::IMG_FONT_ASCII_L},
{'M', CImgData::IMG_FONT_ASCII_M},
{'N', CImgData::IMG_FONT_ASCII_N},
{'O', CImgData::IMG_FONT_ASCII_O},
{'P', CImgData::IMG_FONT_ASCII_P},
{'Q', CImgData::IMG_FONT_ASCII_Q},
{'R', CImgData::IMG_FONT_ASCII_R},
{'S', CImgData::IMG_FONT_ASCII_S},
{'T', CImgData::IMG_FONT_ASCII_T},
{'U', CImgData::IMG_FONT_ASCII_U},
{'V', CImgData::IMG_FONT_ASCII_V},
{'W', CImgData::IMG_FONT_ASCII_W},
{'X', CImgData::IMG_FONT_ASCII_X},
{'Y', CImgData::IMG_FONT_ASCII_Y},
{'Z', CImgData::IMG_FONT_ASCII_Z},
{'[', CImgData::IMG_FONT_ASCII_NAWIAS_PROSTOKATNY_LEWY},
{'\\', CImgData::IMG_FONT_ASCII_BACKSLASH},
{']', CImgData::IMG_FONT_ASCII_NAWIAS_PROSTOKATNY_PRAWY},
{'^', CImgData::IMG_FONT_ASCII_DASZEK},
{'_', CImgData::IMG_FONT_ASCII_PODKRESLNIK},
{'`', CImgData::IMG_FONT_ASCII_GRAWIS},
{'a', CImgData::IMG_FONT_ASCII_a},
{'b', CImgData::IMG_FONT_ASCII_b},
{'c', CImgData::IMG_FONT_ASCII_c},
{'d', CImgData::IMG_FONT_ASCII_d},
{'e', CImgData::IMG_FONT_ASCII_e},
{'f', CImgData::IMG_FONT_ASCII_f},
{'g', CImgData::IMG_FONT_ASCII_g},
{'h', CImgData::IMG_FONT_ASCII_h},
{'i', CImgData::IMG_FONT_ASCII_i},
{'j', CImgData::IMG_FONT_ASCII_j},
{'k', CImgData::IMG_FONT_ASCII_k},
{'l', CImgData::IMG_FONT_ASCII_l},
{'m', CImgData::IMG_FONT_ASCII_m},
{'n', CImgData::IMG_FONT_ASCII_n},
{'o', CImgData::IMG_FONT_ASCII_o},
{'p', CImgData::IMG_FONT_ASCII_p},
{'q', CImgData::IMG_FONT_ASCII_q},
{'r', CImgData::IMG_FONT_ASCII_r},
{'s', CImgData::IMG_FONT_ASCII_s},
{'t', CImgData::IMG_FONT_ASCII_t},
{'u', CImgData::IMG_FONT_ASCII_u},
{'v', CImgData::IMG_FONT_ASCII_v},
{'w', CImgData::IMG_FONT_ASCII_w},
{'x', CImgData::IMG_FONT_ASCII_x},
{'y', CImgData::IMG_FONT_ASCII_y},
{'z', CImgData::IMG_FONT_ASCII_z},
{'{', CImgData::IMG_FONT_ASCII_NAWIAS_KLAMROWY_LEWY},
{'|', CImgData::IMG_FONT_ASCII_KRESKA_PIONOWA},
{'}', CImgData::IMG_FONT_ASCII_NAWIAS_KLAMROWY_PRAWY},
{'~', CImgData::IMG_FONT_ASCII_TYLDA}};

void CFont::init()
{
    CGraphicFont::addFont( //
            CFont::FONT_1,
            CFont::CHAR_MAP_FONT_1,
            sizeof(CHAR_MAP_FONT_1) / sizeof(CHAR_MAP_FONT_1[0]),
            10,
            1);
    CGraphicFont::addFont( //
            CFont::FONT_2,
            CFont::CHAR_MAP_FONT_2,
            sizeof(CHAR_MAP_FONT_2) / sizeof(CHAR_MAP_FONT_2[0]),
            9,
            1);
    CGraphicFont::addFont( //
            CFont::FONT_3,
            CFont::CHAR_MAP_FONT_3,
            sizeof(CHAR_MAP_FONT_3) / sizeof(CHAR_MAP_FONT_3[0]),
            14,
            1);
    CGraphicFont::addFont( //
            CFont::FONT_4,
            CFont::CHAR_MAP_FONT_4,
            sizeof(CHAR_MAP_FONT_4) / sizeof(CHAR_MAP_FONT_4[0]),
            11,
            1);
    CGraphicFont::addFont( //
            CFont::FONT_5,
            CFont::CHAR_MAP_FONT_5,
            sizeof(CHAR_MAP_FONT_5) / sizeof(CHAR_MAP_FONT_5[0]),
            18,
            1);
    CGraphicFont::addFont( //
            CFont::FONT_ASCII,
            CFont::CHAR_MAP_FONT_ASCII,
            sizeof(CHAR_MAP_FONT_ASCII) / sizeof(CHAR_MAP_FONT_ASCII[0]),
            21,
            1);
}

uint32_t CFont::getCharImgAddress(uint16_t fontID, wchar_t charCode)
{
    const CGraphicFont::TImgCharMap *charMap;
    int16_t length;
    switch (fontID)
    {
        case FONT_1:
            charMap = CFont::CHAR_MAP_FONT_1;
            length = sizeof(CHAR_MAP_FONT_1) / sizeof(CHAR_MAP_FONT_1[0]);
        break;

        case FONT_2:
            charMap = CFont::CHAR_MAP_FONT_2;
            length = sizeof(CHAR_MAP_FONT_2) / sizeof(CHAR_MAP_FONT_2[0]);
        break;

        case FONT_3:
            charMap = CFont::CHAR_MAP_FONT_3;
            length = sizeof(CHAR_MAP_FONT_3) / sizeof(CHAR_MAP_FONT_3[0]);
        break;

        case FONT_4:
            charMap = CFont::CHAR_MAP_FONT_4;
            length = sizeof(CHAR_MAP_FONT_4) / sizeof(CHAR_MAP_FONT_4[0]);
        break;

        case FONT_5:
            charMap = CFont::CHAR_MAP_FONT_5;
            length = sizeof(CHAR_MAP_FONT_5) / sizeof(CHAR_MAP_FONT_5[0]);
        break;

        case FONT_ASCII:
            charMap = CFont::CHAR_MAP_FONT_ASCII;
            length = sizeof(CHAR_MAP_FONT_ASCII) / sizeof(CHAR_MAP_FONT_ASCII[0]);
        break;

        default:
            return 0;
    }

    for (int16_t i = 0; i < length; i++)
    {
        if (charMap[i].charCode == charCode)
        {
            return charMap[i].imgAddress;
        }
    }

    return 0;
}
