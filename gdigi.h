/*
 *  Copyright (c) 2009 Tomasz Moń <desowin@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; under version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses>.
 */

#include <usb.h>
#include <glib.h>

enum {
  WAH_TYPE_CRY = 132,
  WAH_TYPE_FULLRANGE = 133,
  WAH_TYPE_CLYDE = 134
};

#define WAH_POSITION_MIN_MAX 20

#define WAH_MIN 8195
#define WAH_MAX 8196

#define WAH_ON_OFF 129
#define WAH_POSITION 3

#define WAH_LEVEL 133

enum {
  COMP_TYPE_DIGI = 195,
  COMP_TYPE_CS = 196
};

#define COMP_ON_OFF 193
#define COMP_POSITION 4

#define COMP_SUSTAIN 208
#define COMP_TONE 209
#define COMP_ATTACK 211
#define COMP_LEVEL 210

enum {
  PICKUP_TYPE_HB_SC = 66,
  PICKUP_TYPE_SC_HB = 65
};

#define PICKUP_ON_OFF 65
#define PICKUP_POSITION 2

enum {
  DIST_TYPE_SCREAMER = 1280,
  DIST_TYPE_808 = 1292,
  DIST_TYPE_GUYOD = 1285,
  DIST_TYPE_DOD250 = 1283,
  DIST_TYPE_RODENT = 1281,
  DIST_TYPE_MX = 1291,
  DIST_TYPE_DS = 1282,
  DIST_TYPE_GRUNGE = 1287,
  DIST_TYPE_ZONE = 1289,
  DIST_TYPE_DEATH = 1294,
  DIST_TYPE_GONK = 1293,
  DIST_TYPE_FUZZY = 1288,
  DIST_TYPE_MP = 1284
};

#define DIST_ON_OFF 2433
#define DIST_POSITION 6

#define DIST_SCREAMER_DRIVE 2434
#define DIST_SCREAMER_TONE  2435
#define DIST_SCREAMER_LVL   2436
#define DIST_808_OVERDRIVE  2473
#define DIST_808_TONE       2474
#define DIST_808_LVL        2475
#define DIST_GUYOD_DRIVE    2448
#define DIST_GUYOD_LVL      2449
#define DIST_DOD250_GAIN    2443
#define DIST_DOD250_LVL     2444
#define DIST_RODENT_DIST    2437
#define DIST_RODENT_FILTER  2438
#define DIST_RODENT_LVL     2439
#define DIST_MX_DIST        2468
#define DIST_MX_OUTPUT      2469
#define DIST_DS_GAIN        2440
#define DIST_DS_TONE        2441
#define DIST_DS_LVL         2442
#define DIST_GRUNGE_GRUNGE  2454
#define DIST_GRUNGE_FACE    2456
#define DIST_GRUNGE_LOUD    2457
#define DIST_GRUNGE_BUTT    2455
#define DIST_ZONE_GAIN      2460
#define DIST_ZONE_LOW       2463
#define DIST_ZONE_MID_LVL   2462
#define DIST_ZONE_MID_FREQ  2461
#define DIST_ZONE_HIGH      2464
#define DIST_ZONE_LEVEL     2465
#define DIST_DEATH_LOW      2477
#define DIST_DEATH_MID      2476
#define DIST_DEATH_HIGH     2479
#define DIST_DEATH_LVL      2478
#define DIST_GONK_GONK      2480
#define DIST_GONK_SMEAR     2471
#define DIST_GONK_SUCK      2470
#define DIST_GONK_HEAVE     2472
#define DIST_FUZZY_FUZZ     2458
#define DIST_FUZZY_VOLUME   2459
#define DIST_MP_SUSTAIN     2445
#define DIST_MP_TONE        2446
#define DIST_MP_VOLUME      2447

#define PRESET_POSITION 18
#define PRESET_LEVEL 2626

enum {
  EQ_TYPE_BRIGHT = 1474,
  EQ_TYPE_MIDBOOST = 1472,
  EQ_TYPE_SCOOP = 1473,
  EQ_TYPE_WARM = 1475
};

#define AMP_POSITION 8

#define AMP_GAIN 2497
#define AMP_LEVEL 2498

#define EQ_ON_OFF 3212
#define EQ_POSITION 24

#define EQ_BASS 3203
#define EQ_MID 3204
#define EQ_TREBLE 3205

enum {
  NOISEGATE_GATE = 768,
  NOISEGATE_SWELL = 769
};

#define NOISEGATE_ON_OFF 705
#define NOISEGATE_POSITION 12

/* available only in Gate mode */
#define NOISEGATE_GATE_TRESHOLD 710
/* available only in Swell mode */
#define NOISEGATE_SWELL_SENS    711
/* available in both Gate and Swell modes */
#define NOISEGATE_ATTACK        712
#define NOISEGATE_RELEASE       713
#define NOISEGATE_ATTN          714

enum {
  CHORUS_TYPE_CE = 0x37B,
  CHORUS_TYPE_DUAL = 0x379,
  CHORUS_TYPE_MULTI = 0x37a,
  CHORUS_TYPE_FLANGER = 0x37d,
  CHORUS_TYPE_MXR_FLANGER = 0x37f,
  CHORUS_TYPE_PHASER = 0x381,
  CHORUS_TYPE_VIBRATO = 0x360,
  CHORUS_TYPE_ROTARY = 0x361,
  CHORUS_TYPE_VIBROPAN = 0x38f,
  CHORUS_TYPE_TREMOLO = 0x35e,
  CHORUS_TYPE_PANNER = 0x35f,
  CHORUS_TYPE_ENVELOPE = 0x38a,
  CHORUS_TYPE_AUTOYA = 0x38b,
  CHORUS_TYPE_YAYA = 0x38c,
  CHORUS_TYPE_STEP_FILTER = 0x38d,
  CHORUS_TYPE_WHAMMY = 0x540,
  CHORUS_TYPE_PITCH_SHIFT = 0x543,
  CHORUS_TYPE_DETUNE = 0x542,
  CHORUS_TYPE_IPS = 0x541
};

#define CHORUSFX_ON_OFF 769
#define CHORUSFX_POSITION 14

#define CE_CHORUS_SPEED 837
#define CE_CHORUS_DEPTH 838

#define DUAL_CHORUS_SPEED 837
#define DUAL_CHORUS_DEPTH 838
#define DUAL_CHORUS_LEVEL 836
#define DUAL_CHORUS_WAVE 840

#define MULTI_CHORUS_SPEED 837
#define MULTI_CHORUS_DEPTH 838
#define MULTI_CHORUS_WAVE  840
#define MULTI_CHORUS_LEVEL 836

#define FLANGER_SPEED 902
#define FLANGER_DEPTH 903
#define FLANGER_REGEN 904
#define FLANGER_LEVEL 901
#define FLANGER_WAVE 905

#define MXR_FLANGER_SPEED 902
#define MXR_FLANGER_WIDTH 914
#define MXR_FLANGER_REGEN 904
#define MXR_FLANGER_MANUAL 917

#define PHASER_SPEED 962
#define PHASER_DEPTH 963
#define PHASER_REGEN 966
#define PHASER_LEVEL 965
#define PHASER_WAVE 967

#define VIBRATO_SPEED 1284
#define VIBRATO_DEPTH 1285

#define ROTARY_SPEED 1346
#define ROTARY_INTENSITY 1348
#define ROTARY_DOPPLER 1350
#define ROTARY_CROSSOVER 1351

#define VIBROPAN_SPEED 1314
#define VIBROPAN_DEPTH 1315
#define VIBROPAN_VIBRA 1316
#define VIBROPAN_WAVE 1317

#define TREMOLO_SPEED 1156
#define TREMOLO_DEPTH 1155
#define TREMOLO_WAVE 1157

#define PANNER_SPEED 1220
#define PANNER_DEPTH 1219
#define PANNER_WAVE 1221

#define ENVELOPE_SENSITIVITY 1606
#define ENVELOPE_RANGE 1605

#define AUTOYA_SPEED 1478
#define AUTOYA_INTENSITY 1482
#define AUTOYA_RANGE 1483

#define YAYA_PEDAL 1410
#define YAYA_INTENSITY 1417
#define YAYA_RANGE 1418

#define STEP_FILTER_SPEED 3010
#define STEP_FILTER_INTENSITY 3011

#define WHAMMY_AMOUNT 1797
#define WHAMMY_PEDAL 1795
#define WHAMMY_MIX 1796

#define PITCH_AMOUNT 1730
#define PITCH_MIX 1745

#define DETUNE_AMOUNT 1668
#define DETUNE_LEVEL 1667

#define IPS_SHIFT_AMOUNT 2754
#define IPS_KEY 2756
#define IPS_SCALE 2755
#define IPS_LEVEL 2757

/* DUAL_CHORUS_WAVE, MULTI_CHORUS_WAVE, FLANGER_WAVE, PHASER_WAVE,
   VIBROPAN_WAVE, TREMOLO_WAVE, PANNER_WAVE valid values */
#define WAVE_TRI    0x00
#define WAVE_SINE   0x01
#define WAVE_SQUARE 0x02

/* WHAMMY_AMOUNT valid values */
#define WHAMMY_OCT_UP 0x00
#define WHAMMY_2OCT_UP 0x01
#define WHAMMY_2ND_DN 0x02
#define WHAMMY_RV_2ND 0x03
#define WHAMMY_4TH_DN 0x04
#define WHAMMY_OCT_DN 0x05
#define WHAMMY_2OCT_DN 0x06
#define WHAMMY_DIV_BMB 0x07
#define WHAMMY_M3_MA 0x08
#define WHAMMY_2ND_MA3 0x09
#define WHAMMY_3RD_4TH 0x0A
#define WHAMMY_4TH_5TH 0x0B
#define WHAMMY_5TH_OCT 0x0C
#define WHAMMY_HOCT_UP 0x0D
#define WHAMMY_HOCT_DN 0x0E
#define WHAMMY_OCT_UD 0x0F

/* IPS_SHIFT_AMOUNT valid values */
#define IPS_OCT_D 0x00
#define IPS_7TH_DN 0x01
#define IPS_6TH_DN 0x02
#define IPS_5TH_DN 0x03
#define IPS_4TH_DN 0x04
#define IPS_3RD_DN 0x05
#define IPS_2ND_DN 0x06
#define IPS_2ND_UP 0x07
#define IPS_3RD_UP 0x08
#define IPS_4TH_UP 0x09
#define IPS_5TH_UP 0x0A
#define IPS_6TH_UP 0x0B
#define IPS_7TH_UP 0x0C
#define IPS_OCT_U 0x0D

/* IPS_KEY valid values */
#define IPS_E 0x00
#define IPS_F 0x01
#define IPS_GB 0x02
#define IPS_G 0x03
#define IPS_AB 0x04
#define IPS_A 0x05
#define IPS_BB 0x06
#define IPS_B 0x07
#define IPS_C 0x08
#define IPS_DD 0x09
#define IPS_D 0x0A
#define IPS_EB 0x0B

/* IPS_SCALE valid values */
#define IPS_MAJOR 0x00
#define IPS_MINOR 0x01
#define IPS_DORIA 0x02
#define IPS_MIXLYD 0x03
#define IPS_LYDIAN 0x04
#define IPS_HMINO 0x05

enum {
  DELAY_TYPE_ANALOG = 1046,
  DELAY_TYPE_DIGITAL = 1045,
  DELAY_TYPE_MODULATED = 1047,
  DELAY_TYPE_PONG = 1048,
  DELAY_TYPE_TAPE = 1049
};

#define DELAY_ON_OFF 1857
#define DELAY_POSITION 15

#define ANALOG_LEVEL 1860
#define ANALOG_REPEATS 1863

#define DIGITAL_LEVEL 1860
#define DIGITAL_REPEATS 1863
#define DIGITAL_DUCKER_THRESH 1889
#define DIGITAL_DUCKER_LEVEL 1890

#define MODULATED_LEVEL 1860
#define MODULATED_REPEATS 1863
#define MODULATED_DEPTH 1873

#define PONG_LEVEL 1860
#define PONG_REPEATS 1863
#define PONG_DUCKER_THRESH 1889
#define PONG_DUCKER_LEVEL 1890

#define TAPE_LEVEL 1860
#define TAPE_REPEATS 1863
#define TAPE_WOW 1891
#define TAPE_FLUTTER 1892

enum {
  REVERB_TYPE_TWIN = 1146,
  REVERB_TYPE_LEX_AMBIENCE = 1150,
  REVERB_TYPE_LEX_STUDIO = 1149,
  REVERB_TYPE_LEX_ROOM = 1148,
  REVERB_TYPE_LEX_HALL = 1147,
  REVERB_TYPE_EMT240_PLATE = 1151
};

#define REVERB_ON_OFF 1921
#define REVERB_POSITION 16

#define TWIN_REVERB 1925

#define LEX_AMBIENCE_PREDELAY 1922
#define LEX_AMBIENCE_DECAY 1927
#define LEX_AMBIENCE_LIVELINESS 1933
#define LEX_AMBIENCE_LEVEL 1925

#define LEX_STUDIO_PREDELAY 1922
#define LEX_STUDIO_DECAY 1927
#define LEX_STUDIO_LIVELINESS 1933
#define LEX_STUDIO_LEVEL 1925

#define LEX_ROOM_PREDELAY 1922
#define LEX_ROOM_DECAY 1927
#define LEX_ROOM_LIVELINESS 1933
#define LEX_ROOM_LEVEL 1925

#define LEX_HALL_PREDELAY 1922
#define LEX_HALL_DECAY 1927
#define LEX_HALL_LIVELINESS 1933
#define LEX_HALL_LEVEL 1925

#define EMT240_PLATE_PREDELAY 1922
#define EMT240_PLATE_DECAY 1927
#define EMT240_PLATE_LIVELINESS 1933
#define EMT240_PLATE_LEVEL 1925

void set_wah_min(int level);
void set_wah_max(int level);
void set_wah_level(int level);
void set_wah_type(int type);
void set_wah_on_off(gboolean val);
void set_comp_sustain(int level);
void set_comp_tone(int level);
void set_comp_attack(int level);
void set_comp_level(int level);
void set_comp_type(int type);
void set_comp_on_off(gboolean val);
void switch_user_preset(int x);
void switch_system_preset(int x);
void set_pickup_type(int type);
void set_pickup_on_off(gboolean val);
void set_dist_type(int type);
void set_dist_option(guint32 option, int value);
void set_dist_on_off(gboolean val);
void set_preset_level(int level);
void set_eq_type(int type);
void set_eq_gain(int x);
void set_eq_level(int x);
void set_eq_bass(int x);
void set_eq_mid(int x);
void set_eq_mid_hz(int x);
void set_eq_treble(int x);
void set_eq_treb_hz(int x);
void set_eq_on_off(gboolean val);
void set_noisegate_type(int type);
void set_gate_option(guint32 option, int x);
void set_noisegate_on_off(gboolean val);
void set_chorusfx_option(guint32 option, int x);
void set_chorusfx_type(int type);
void set_chorusfx_on_off(gboolean val);
void set_delay_time(int x);
void set_delay_type(int type);
void set_delay_option(guint32 option, int x);
void set_delay_on_off(gboolean val);
void set_reverb_option(guint32 option, int x);
void set_reverb_type(int type);
void set_reverb_on_off(gboolean val);