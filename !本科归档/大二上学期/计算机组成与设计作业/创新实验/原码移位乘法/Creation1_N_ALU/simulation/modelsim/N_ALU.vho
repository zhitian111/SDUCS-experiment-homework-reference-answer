-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 13.1.0 Build 162 10/23/2013 SJ Full Version"

-- DATE "12/23/2024 20:50:13"

-- 
-- Device: Altera EP4CE6E22C7 Package TQFP144
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	N_ALU IS
    PORT (
	F0 : OUT std_logic;
	B0 : IN std_logic;
	A0 : IN std_logic;
	A1 : IN std_logic;
	B1 : IN std_logic;
	A3 : IN std_logic;
	B2 : IN std_logic;
	A2 : IN std_logic;
	M : IN std_logic;
	CN : IN std_logic;
	B3 : IN std_logic;
	S2 : IN std_logic;
	S1 : IN std_logic;
	S0 : IN std_logic;
	S3 : IN std_logic;
	F1 : OUT std_logic;
	F2 : OUT std_logic;
	F3 : OUT std_logic;
	AEQ : OUT std_logic;
	GN : OUT std_logic;
	PN : OUT std_logic;
	CN4 : OUT std_logic
	);
END N_ALU;

-- Design Ports Information
-- F0	=>  Location: PIN_99,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- F1	=>  Location: PIN_106,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- F2	=>  Location: PIN_38,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- F3	=>  Location: PIN_114,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- AEQ	=>  Location: PIN_138,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- GN	=>  Location: PIN_121,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- PN	=>  Location: PIN_104,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- CN4	=>  Location: PIN_49,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- CN	=>  Location: PIN_67,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- M	=>  Location: PIN_66,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- S2	=>  Location: PIN_52,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- S3	=>  Location: PIN_58,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B0	=>  Location: PIN_32,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A0	=>  Location: PIN_55,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- S1	=>  Location: PIN_33,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- S0	=>  Location: PIN_51,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B1	=>  Location: PIN_44,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A1	=>  Location: PIN_42,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B2	=>  Location: PIN_46,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A2	=>  Location: PIN_24,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B3	=>  Location: PIN_25,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A3	=>  Location: PIN_142,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF N_ALU IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_F0 : std_logic;
SIGNAL ww_B0 : std_logic;
SIGNAL ww_A0 : std_logic;
SIGNAL ww_A1 : std_logic;
SIGNAL ww_B1 : std_logic;
SIGNAL ww_A3 : std_logic;
SIGNAL ww_B2 : std_logic;
SIGNAL ww_A2 : std_logic;
SIGNAL ww_M : std_logic;
SIGNAL ww_CN : std_logic;
SIGNAL ww_B3 : std_logic;
SIGNAL ww_S2 : std_logic;
SIGNAL ww_S1 : std_logic;
SIGNAL ww_S0 : std_logic;
SIGNAL ww_S3 : std_logic;
SIGNAL ww_F1 : std_logic;
SIGNAL ww_F2 : std_logic;
SIGNAL ww_F3 : std_logic;
SIGNAL ww_AEQ : std_logic;
SIGNAL ww_GN : std_logic;
SIGNAL ww_PN : std_logic;
SIGNAL ww_CN4 : std_logic;
SIGNAL \F0~output_o\ : std_logic;
SIGNAL \F1~output_o\ : std_logic;
SIGNAL \F2~output_o\ : std_logic;
SIGNAL \F3~output_o\ : std_logic;
SIGNAL \AEQ~output_o\ : std_logic;
SIGNAL \GN~output_o\ : std_logic;
SIGNAL \PN~output_o\ : std_logic;
SIGNAL \CN4~output_o\ : std_logic;
SIGNAL \S0~input_o\ : std_logic;
SIGNAL \B0~input_o\ : std_logic;
SIGNAL \S1~input_o\ : std_logic;
SIGNAL \A0~input_o\ : std_logic;
SIGNAL \inst|43~0_combout\ : std_logic;
SIGNAL \S2~input_o\ : std_logic;
SIGNAL \S3~input_o\ : std_logic;
SIGNAL \inst|46~0_combout\ : std_logic;
SIGNAL \M~input_o\ : std_logic;
SIGNAL \CN~input_o\ : std_logic;
SIGNAL \inst|80~0_combout\ : std_logic;
SIGNAL \A1~input_o\ : std_logic;
SIGNAL \B1~input_o\ : std_logic;
SIGNAL \inst|47~0_combout\ : std_logic;
SIGNAL \inst|44~0_combout\ : std_logic;
SIGNAL \inst|79~combout\ : std_logic;
SIGNAL \inst|81~combout\ : std_logic;
SIGNAL \A3~input_o\ : std_logic;
SIGNAL \B3~input_o\ : std_logic;
SIGNAL \inst|52~0_combout\ : std_logic;
SIGNAL \inst|51~0_combout\ : std_logic;
SIGNAL \A2~input_o\ : std_logic;
SIGNAL \B2~input_o\ : std_logic;
SIGNAL \inst|45~0_combout\ : std_logic;
SIGNAL \inst|48~0_combout\ : std_logic;
SIGNAL \inst|77~0_combout\ : std_logic;
SIGNAL \inst|77~1_combout\ : std_logic;
SIGNAL \inst|77~2_combout\ : std_logic;
SIGNAL \inst|77~3_combout\ : std_logic;
SIGNAL \inst|83~0_combout\ : std_logic;
SIGNAL \inst|83~1_combout\ : std_logic;
SIGNAL \inst|63~0_combout\ : std_logic;
SIGNAL \inst|63~1_combout\ : std_logic;
SIGNAL \inst|60~0_combout\ : std_logic;
SIGNAL \inst|78~combout\ : std_logic;
SIGNAL \inst|ALT_INV_60~0_combout\ : std_logic;
SIGNAL \inst|ALT_INV_63~1_combout\ : std_logic;
SIGNAL \inst|ALT_INV_77~3_combout\ : std_logic;

BEGIN

F0 <= ww_F0;
ww_B0 <= B0;
ww_A0 <= A0;
ww_A1 <= A1;
ww_B1 <= B1;
ww_A3 <= A3;
ww_B2 <= B2;
ww_A2 <= A2;
ww_M <= M;
ww_CN <= CN;
ww_B3 <= B3;
ww_S2 <= S2;
ww_S1 <= S1;
ww_S0 <= S0;
ww_S3 <= S3;
F1 <= ww_F1;
F2 <= ww_F2;
F3 <= ww_F3;
AEQ <= ww_AEQ;
GN <= ww_GN;
PN <= ww_PN;
CN4 <= ww_CN4;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\inst|ALT_INV_60~0_combout\ <= NOT \inst|60~0_combout\;
\inst|ALT_INV_63~1_combout\ <= NOT \inst|63~1_combout\;
\inst|ALT_INV_77~3_combout\ <= NOT \inst|77~3_combout\;

-- Location: IOOBUF_X34_Y17_N16
\F0~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|80~0_combout\,
	devoe => ww_devoe,
	o => \F0~output_o\);

-- Location: IOOBUF_X34_Y20_N9
\F1~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|81~combout\,
	devoe => ww_devoe,
	o => \F1~output_o\);

-- Location: IOOBUF_X1_Y0_N23
\F2~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \F2~output_o\);

-- Location: IOOBUF_X28_Y24_N16
\F3~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|ALT_INV_77~3_combout\,
	devoe => ww_devoe,
	o => \F3~output_o\);

-- Location: IOOBUF_X7_Y24_N9
\AEQ~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|83~1_combout\,
	devoe => ww_devoe,
	o => \AEQ~output_o\);

-- Location: IOOBUF_X23_Y24_N16
\GN~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|ALT_INV_63~1_combout\,
	devoe => ww_devoe,
	o => \GN~output_o\);

-- Location: IOOBUF_X34_Y18_N2
\PN~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|ALT_INV_60~0_combout\,
	devoe => ww_devoe,
	o => \PN~output_o\);

-- Location: IOOBUF_X13_Y0_N16
\CN4~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|78~combout\,
	devoe => ww_devoe,
	o => \CN4~output_o\);

-- Location: IOIBUF_X16_Y0_N22
\S0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_S0,
	o => \S0~input_o\);

-- Location: IOIBUF_X0_Y6_N15
\B0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B0,
	o => \B0~input_o\);

-- Location: IOIBUF_X0_Y6_N22
\S1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_S1,
	o => \S1~input_o\);

-- Location: IOIBUF_X18_Y0_N15
\A0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A0,
	o => \A0~input_o\);

-- Location: LCCOMB_X4_Y9_N2
\inst|43~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|43~0_combout\ = ((\B0~input_o\ & ((\S1~input_o\))) # (!\B0~input_o\ & (\S0~input_o\))) # (!\A0~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110001011111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \S0~input_o\,
	datab => \B0~input_o\,
	datac => \S1~input_o\,
	datad => \A0~input_o\,
	combout => \inst|43~0_combout\);

-- Location: IOIBUF_X16_Y0_N8
\S2~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_S2,
	o => \S2~input_o\);

-- Location: IOIBUF_X21_Y0_N8
\S3~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_S3,
	o => \S3~input_o\);

-- Location: LCCOMB_X4_Y9_N0
\inst|46~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|46~0_combout\ = (!\A0~input_o\ & ((\B0~input_o\ & (\S2~input_o\)) # (!\B0~input_o\ & ((\S3~input_o\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \B0~input_o\,
	datab => \S2~input_o\,
	datac => \S3~input_o\,
	datad => \A0~input_o\,
	combout => \inst|46~0_combout\);

-- Location: IOIBUF_X28_Y0_N1
\M~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_M,
	o => \M~input_o\);

-- Location: IOIBUF_X30_Y0_N22
\CN~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_CN,
	o => \CN~input_o\);

-- Location: LCCOMB_X28_Y9_N8
\inst|80~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|80~0_combout\ = \inst|43~0_combout\ $ (\inst|46~0_combout\ $ (((!\M~input_o\ & \CN~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100101100110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|43~0_combout\,
	datab => \inst|46~0_combout\,
	datac => \M~input_o\,
	datad => \CN~input_o\,
	combout => \inst|80~0_combout\);

-- Location: IOIBUF_X3_Y0_N1
\A1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A1,
	o => \A1~input_o\);

-- Location: IOIBUF_X5_Y0_N15
\B1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B1,
	o => \B1~input_o\);

-- Location: LCCOMB_X4_Y9_N20
\inst|47~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|47~0_combout\ = (!\A1~input_o\ & ((\B1~input_o\ & ((\S2~input_o\))) # (!\B1~input_o\ & (\S3~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A1~input_o\,
	datab => \B1~input_o\,
	datac => \S3~input_o\,
	datad => \S2~input_o\,
	combout => \inst|47~0_combout\);

-- Location: LCCOMB_X4_Y9_N6
\inst|44~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|44~0_combout\ = ((\B1~input_o\ & (\S1~input_o\)) # (!\B1~input_o\ & ((\S0~input_o\)))) # (!\A1~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111110001111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \S1~input_o\,
	datab => \B1~input_o\,
	datac => \A1~input_o\,
	datad => \S0~input_o\,
	combout => \inst|44~0_combout\);

-- Location: LCCOMB_X28_Y9_N2
\inst|79\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|79~combout\ = (!\M~input_o\ & (((!\inst|46~0_combout\ & \CN~input_o\)) # (!\inst|43~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000011100000101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|43~0_combout\,
	datab => \inst|46~0_combout\,
	datac => \M~input_o\,
	datad => \CN~input_o\,
	combout => \inst|79~combout\);

-- Location: LCCOMB_X28_Y9_N12
\inst|81\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|81~combout\ = \inst|47~0_combout\ $ (\inst|44~0_combout\ $ (\inst|79~combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001100101100110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|47~0_combout\,
	datab => \inst|44~0_combout\,
	datad => \inst|79~combout\,
	combout => \inst|81~combout\);

-- Location: IOIBUF_X3_Y24_N22
\A3~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A3,
	o => \A3~input_o\);

-- Location: IOIBUF_X0_Y11_N22
\B3~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B3,
	o => \B3~input_o\);

-- Location: LCCOMB_X4_Y9_N4
\inst|52~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|52~0_combout\ = (!\A3~input_o\ & ((\B3~input_o\ & ((\S2~input_o\))) # (!\B3~input_o\ & (\S3~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A3~input_o\,
	datab => \B3~input_o\,
	datac => \S3~input_o\,
	datad => \S2~input_o\,
	combout => \inst|52~0_combout\);

-- Location: LCCOMB_X4_Y9_N30
\inst|51~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|51~0_combout\ = ((\B3~input_o\ & (\S1~input_o\)) # (!\B3~input_o\ & ((\S0~input_o\)))) # (!\A3~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111011111010101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \A3~input_o\,
	datab => \B3~input_o\,
	datac => \S1~input_o\,
	datad => \S0~input_o\,
	combout => \inst|51~0_combout\);

-- Location: IOIBUF_X0_Y11_N15
\A2~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A2,
	o => \A2~input_o\);

-- Location: IOIBUF_X7_Y0_N1
\B2~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B2,
	o => \B2~input_o\);

-- Location: LCCOMB_X4_Y9_N8
\inst|45~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|45~0_combout\ = ((\B2~input_o\ & (\S1~input_o\)) # (!\B2~input_o\ & ((\S0~input_o\)))) # (!\A2~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011111110110011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \S1~input_o\,
	datab => \A2~input_o\,
	datac => \B2~input_o\,
	datad => \S0~input_o\,
	combout => \inst|45~0_combout\);

-- Location: LCCOMB_X4_Y9_N10
\inst|48~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|48~0_combout\ = (!\A2~input_o\ & ((\B2~input_o\ & ((\S2~input_o\))) # (!\B2~input_o\ & (\S3~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001000010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \B2~input_o\,
	datab => \A2~input_o\,
	datac => \S3~input_o\,
	datad => \S2~input_o\,
	combout => \inst|48~0_combout\);

-- Location: LCCOMB_X28_Y9_N14
\inst|77~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|77~0_combout\ = (\inst|43~0_combout\ & (\inst|44~0_combout\ & ((\inst|46~0_combout\) # (!\CN~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|43~0_combout\,
	datab => \inst|46~0_combout\,
	datac => \inst|44~0_combout\,
	datad => \CN~input_o\,
	combout => \inst|77~0_combout\);

-- Location: LCCOMB_X28_Y9_N24
\inst|77~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|77~1_combout\ = (\inst|77~0_combout\) # ((\inst|47~0_combout\ & \inst|44~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111100011111000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|47~0_combout\,
	datab => \inst|44~0_combout\,
	datac => \inst|77~0_combout\,
	combout => \inst|77~1_combout\);

-- Location: LCCOMB_X28_Y9_N18
\inst|77~2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|77~2_combout\ = (\M~input_o\) # ((\inst|45~0_combout\ & ((\inst|48~0_combout\) # (\inst|77~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101011111000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|45~0_combout\,
	datab => \inst|48~0_combout\,
	datac => \M~input_o\,
	datad => \inst|77~1_combout\,
	combout => \inst|77~2_combout\);

-- Location: LCCOMB_X28_Y9_N20
\inst|77~3\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|77~3_combout\ = \inst|52~0_combout\ $ (\inst|51~0_combout\ $ (\inst|77~2_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100111100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst|52~0_combout\,
	datac => \inst|51~0_combout\,
	datad => \inst|77~2_combout\,
	combout => \inst|77~3_combout\);

-- Location: LCCOMB_X28_Y9_N30
\inst|83~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|83~0_combout\ = \inst|45~0_combout\ $ (\inst|48~0_combout\ $ (((\M~input_o\) # (\inst|77~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001100110010110",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|45~0_combout\,
	datab => \inst|48~0_combout\,
	datac => \M~input_o\,
	datad => \inst|77~1_combout\,
	combout => \inst|83~0_combout\);

-- Location: LCCOMB_X28_Y9_N0
\inst|83~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|83~1_combout\ = (!\inst|81~combout\ & (!\inst|80~0_combout\ & (\inst|83~0_combout\ & \inst|77~3_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|81~combout\,
	datab => \inst|80~0_combout\,
	datac => \inst|83~0_combout\,
	datad => \inst|77~3_combout\,
	combout => \inst|83~1_combout\);

-- Location: LCCOMB_X28_Y9_N10
\inst|63~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|63~0_combout\ = (\inst|48~0_combout\) # ((\inst|44~0_combout\ & ((\inst|43~0_combout\) # (\inst|47~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|43~0_combout\,
	datab => \inst|48~0_combout\,
	datac => \inst|47~0_combout\,
	datad => \inst|44~0_combout\,
	combout => \inst|63~0_combout\);

-- Location: LCCOMB_X28_Y9_N4
\inst|63~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|63~1_combout\ = ((!\inst|52~0_combout\ & ((!\inst|63~0_combout\) # (!\inst|45~0_combout\)))) # (!\inst|51~0_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0001111100111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|45~0_combout\,
	datab => \inst|52~0_combout\,
	datac => \inst|51~0_combout\,
	datad => \inst|63~0_combout\,
	combout => \inst|63~1_combout\);

-- Location: LCCOMB_X28_Y9_N22
\inst|60~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|60~0_combout\ = (!\inst|47~0_combout\ & (!\inst|52~0_combout\ & (!\inst|46~0_combout\ & !\inst|48~0_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|47~0_combout\,
	datab => \inst|52~0_combout\,
	datac => \inst|46~0_combout\,
	datad => \inst|48~0_combout\,
	combout => \inst|60~0_combout\);

-- Location: LCCOMB_X28_Y9_N16
\inst|78\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|78~combout\ = (\inst|63~1_combout\) # ((\inst|60~0_combout\ & \CN~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110011001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst|63~1_combout\,
	datac => \inst|60~0_combout\,
	datad => \CN~input_o\,
	combout => \inst|78~combout\);

ww_F0 <= \F0~output_o\;

ww_F1 <= \F1~output_o\;

ww_F2 <= \F2~output_o\;

ww_F3 <= \F3~output_o\;

ww_AEQ <= \AEQ~output_o\;

ww_GN <= \GN~output_o\;

ww_PN <= \PN~output_o\;

ww_CN4 <= \CN4~output_o\;
END structure;


