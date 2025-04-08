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

-- DATE "12/23/2024 20:55:32"

-- 
-- Device: Altera EP4CE6E22C7 Package TQFP144
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY ALTERA;
LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Block1 IS
    PORT (
	q1 : OUT std_logic;
	b8 : IN std_logic;
	a7 : IN std_logic;
	a6 : IN std_logic;
	a8 : IN std_logic;
	a5 : IN std_logic;
	a2 : IN std_logic;
	a3 : IN std_logic;
	a4 : IN std_logic;
	a1 : IN std_logic;
	CLK : IN std_logic;
	CLR : IN std_logic;
	s0 : IN std_logic;
	s1 : IN std_logic;
	b4 : IN std_logic;
	b7 : IN std_logic;
	b6 : IN std_logic;
	b5 : IN std_logic;
	b1 : IN std_logic;
	b2 : IN std_logic;
	b3 : IN std_logic;
	q2 : OUT std_logic;
	q3 : OUT std_logic;
	q4 : OUT std_logic;
	q6 : OUT std_logic;
	q7 : OUT std_logic;
	q8 : OUT std_logic;
	q9 : OUT std_logic;
	q10 : OUT std_logic;
	q11 : OUT std_logic;
	q12 : OUT std_logic;
	q13 : OUT std_logic;
	q14 : OUT std_logic;
	q15 : OUT std_logic;
	q16 : OUT std_logic;
	q5 : OUT std_logic
	);
END Block1;

-- Design Ports Information
-- q1	=>  Location: PIN_72,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a7	=>  Location: PIN_104,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a6	=>  Location: PIN_85,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a8	=>  Location: PIN_38,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a5	=>  Location: PIN_127,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a2	=>  Location: PIN_120,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a3	=>  Location: PIN_42,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a4	=>  Location: PIN_110,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a1	=>  Location: PIN_121,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q2	=>  Location: PIN_67,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q3	=>  Location: PIN_75,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q4	=>  Location: PIN_68,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q6	=>  Location: PIN_74,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q7	=>  Location: PIN_69,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q8	=>  Location: PIN_76,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q9	=>  Location: PIN_43,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q10	=>  Location: PIN_137,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q11	=>  Location: PIN_64,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q12	=>  Location: PIN_141,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q13	=>  Location: PIN_124,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q14	=>  Location: PIN_112,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q15	=>  Location: PIN_125,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q16	=>  Location: PIN_31,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- q5	=>  Location: PIN_77,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- s1	=>  Location: PIN_65,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- s0	=>  Location: PIN_73,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b1	=>  Location: PIN_88,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- CLR	=>  Location: PIN_23,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b2	=>  Location: PIN_89,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b3	=>  Location: PIN_80,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b4	=>  Location: PIN_90,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b6	=>  Location: PIN_91,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b7	=>  Location: PIN_71,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b8	=>  Location: PIN_70,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b5	=>  Location: PIN_84,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- CLK	=>  Location: PIN_87,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Block1 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_q1 : std_logic;
SIGNAL ww_b8 : std_logic;
SIGNAL ww_a7 : std_logic;
SIGNAL ww_a6 : std_logic;
SIGNAL ww_a8 : std_logic;
SIGNAL ww_a5 : std_logic;
SIGNAL ww_a2 : std_logic;
SIGNAL ww_a3 : std_logic;
SIGNAL ww_a4 : std_logic;
SIGNAL ww_a1 : std_logic;
SIGNAL ww_CLK : std_logic;
SIGNAL ww_CLR : std_logic;
SIGNAL ww_s0 : std_logic;
SIGNAL ww_s1 : std_logic;
SIGNAL ww_b4 : std_logic;
SIGNAL ww_b7 : std_logic;
SIGNAL ww_b6 : std_logic;
SIGNAL ww_b5 : std_logic;
SIGNAL ww_b1 : std_logic;
SIGNAL ww_b2 : std_logic;
SIGNAL ww_b3 : std_logic;
SIGNAL ww_q2 : std_logic;
SIGNAL ww_q3 : std_logic;
SIGNAL ww_q4 : std_logic;
SIGNAL ww_q6 : std_logic;
SIGNAL ww_q7 : std_logic;
SIGNAL ww_q8 : std_logic;
SIGNAL ww_q9 : std_logic;
SIGNAL ww_q10 : std_logic;
SIGNAL ww_q11 : std_logic;
SIGNAL ww_q12 : std_logic;
SIGNAL ww_q13 : std_logic;
SIGNAL ww_q14 : std_logic;
SIGNAL ww_q15 : std_logic;
SIGNAL ww_q16 : std_logic;
SIGNAL ww_q5 : std_logic;
SIGNAL \inst18~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \CLR~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \a7~input_o\ : std_logic;
SIGNAL \a6~input_o\ : std_logic;
SIGNAL \a8~input_o\ : std_logic;
SIGNAL \a5~input_o\ : std_logic;
SIGNAL \a2~input_o\ : std_logic;
SIGNAL \a3~input_o\ : std_logic;
SIGNAL \a4~input_o\ : std_logic;
SIGNAL \a1~input_o\ : std_logic;
SIGNAL \q1~output_o\ : std_logic;
SIGNAL \q2~output_o\ : std_logic;
SIGNAL \q3~output_o\ : std_logic;
SIGNAL \q4~output_o\ : std_logic;
SIGNAL \q6~output_o\ : std_logic;
SIGNAL \q7~output_o\ : std_logic;
SIGNAL \q8~output_o\ : std_logic;
SIGNAL \q9~output_o\ : std_logic;
SIGNAL \q10~output_o\ : std_logic;
SIGNAL \q11~output_o\ : std_logic;
SIGNAL \q12~output_o\ : std_logic;
SIGNAL \q13~output_o\ : std_logic;
SIGNAL \q14~output_o\ : std_logic;
SIGNAL \q15~output_o\ : std_logic;
SIGNAL \q16~output_o\ : std_logic;
SIGNAL \q5~output_o\ : std_logic;
SIGNAL \CLK~input_o\ : std_logic;
SIGNAL \inst16~feeder_combout\ : std_logic;
SIGNAL \inst14|sub|9~0_combout\ : std_logic;
SIGNAL \CLR~input_o\ : std_logic;
SIGNAL \CLR~inputclkctrl_outclk\ : std_logic;
SIGNAL \inst14|sub|9~q\ : std_logic;
SIGNAL \inst14|sub|90~combout\ : std_logic;
SIGNAL \inst14|sub|87~q\ : std_logic;
SIGNAL \inst14|sub|97~combout\ : std_logic;
SIGNAL \inst14|sub|99~q\ : std_logic;
SIGNAL \inst14|sub|107~combout\ : std_logic;
SIGNAL \inst14|sub|110~q\ : std_logic;
SIGNAL \inst16~q\ : std_logic;
SIGNAL \inst18~combout\ : std_logic;
SIGNAL \inst18~clkctrl_outclk\ : std_logic;
SIGNAL \s1~input_o\ : std_logic;
SIGNAL \s0~input_o\ : std_logic;
SIGNAL \b1~input_o\ : std_logic;
SIGNAL \inst2|120~0_combout\ : std_logic;
SIGNAL \b2~input_o\ : std_logic;
SIGNAL \b4~input_o\ : std_logic;
SIGNAL \b5~input_o\ : std_logic;
SIGNAL \b6~input_o\ : std_logic;
SIGNAL \b7~input_o\ : std_logic;
SIGNAL \inst2|122~0_combout\ : std_logic;
SIGNAL \b8~input_o\ : std_logic;
SIGNAL \inst2|121~0_combout\ : std_logic;
SIGNAL \inst2|121~1_combout\ : std_logic;
SIGNAL \inst2|113~q\ : std_logic;
SIGNAL \inst2|122~1_combout\ : std_logic;
SIGNAL \inst2|114~q\ : std_logic;
SIGNAL \inst2|123~0_combout\ : std_logic;
SIGNAL \inst2|123~1_combout\ : std_logic;
SIGNAL \inst2|115~q\ : std_logic;
SIGNAL \inst2|124~0_combout\ : std_logic;
SIGNAL \inst2|124~1_combout\ : std_logic;
SIGNAL \inst2|116~q\ : std_logic;
SIGNAL \inst2|125~0_combout\ : std_logic;
SIGNAL \inst2|125~1_combout\ : std_logic;
SIGNAL \inst2|117~q\ : std_logic;
SIGNAL \b3~input_o\ : std_logic;
SIGNAL \inst2|126~0_combout\ : std_logic;
SIGNAL \inst2|126~1_combout\ : std_logic;
SIGNAL \inst2|118~q\ : std_logic;
SIGNAL \inst2|127~0_combout\ : std_logic;
SIGNAL \inst2|127~1_combout\ : std_logic;
SIGNAL \inst2|119~q\ : std_logic;
SIGNAL \inst2|120~1_combout\ : std_logic;
SIGNAL \inst2|120~q\ : std_logic;
SIGNAL \inst14|sub|ALT_INV_110~q\ : std_logic;

BEGIN

q1 <= ww_q1;
ww_b8 <= b8;
ww_a7 <= a7;
ww_a6 <= a6;
ww_a8 <= a8;
ww_a5 <= a5;
ww_a2 <= a2;
ww_a3 <= a3;
ww_a4 <= a4;
ww_a1 <= a1;
ww_CLK <= CLK;
ww_CLR <= CLR;
ww_s0 <= s0;
ww_s1 <= s1;
ww_b4 <= b4;
ww_b7 <= b7;
ww_b6 <= b6;
ww_b5 <= b5;
ww_b1 <= b1;
ww_b2 <= b2;
ww_b3 <= b3;
q2 <= ww_q2;
q3 <= ww_q3;
q4 <= ww_q4;
q6 <= ww_q6;
q7 <= ww_q7;
q8 <= ww_q8;
q9 <= ww_q9;
q10 <= ww_q10;
q11 <= ww_q11;
q12 <= ww_q12;
q13 <= ww_q13;
q14 <= ww_q14;
q15 <= ww_q15;
q16 <= ww_q16;
q5 <= ww_q5;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\inst18~clkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \inst18~combout\);

\CLR~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \CLR~input_o\);
\inst14|sub|ALT_INV_110~q\ <= NOT \inst14|sub|110~q\;

-- Location: IOOBUF_X32_Y0_N9
\q1~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|120~q\,
	devoe => ww_devoe,
	o => \q1~output_o\);

-- Location: IOOBUF_X30_Y0_N23
\q2~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|119~q\,
	devoe => ww_devoe,
	o => \q2~output_o\);

-- Location: IOOBUF_X34_Y3_N23
\q3~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|118~q\,
	devoe => ww_devoe,
	o => \q3~output_o\);

-- Location: IOOBUF_X30_Y0_N9
\q4~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|117~q\,
	devoe => ww_devoe,
	o => \q4~output_o\);

-- Location: IOOBUF_X34_Y2_N16
\q6~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|115~q\,
	devoe => ww_devoe,
	o => \q6~output_o\);

-- Location: IOOBUF_X30_Y0_N2
\q7~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|114~q\,
	devoe => ww_devoe,
	o => \q7~output_o\);

-- Location: IOOBUF_X34_Y4_N23
\q8~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|113~q\,
	devoe => ww_devoe,
	o => \q8~output_o\);

-- Location: IOOBUF_X5_Y0_N23
\q9~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \q9~output_o\);

-- Location: IOOBUF_X7_Y24_N2
\q10~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \q10~output_o\);

-- Location: IOOBUF_X25_Y0_N2
\q11~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \q11~output_o\);

-- Location: IOOBUF_X5_Y24_N9
\q12~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \q12~output_o\);

-- Location: IOOBUF_X18_Y24_N16
\q13~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \q13~output_o\);

-- Location: IOOBUF_X28_Y24_N2
\q14~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \q14~output_o\);

-- Location: IOOBUF_X18_Y24_N23
\q15~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \q15~output_o\);

-- Location: IOOBUF_X0_Y7_N2
\q16~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => GND,
	devoe => ww_devoe,
	o => \q16~output_o\);

-- Location: IOOBUF_X34_Y4_N16
\q5~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|116~q\,
	devoe => ww_devoe,
	o => \q5~output_o\);

-- Location: IOIBUF_X34_Y10_N8
\CLK~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_CLK,
	o => \CLK~input_o\);

-- Location: LCCOMB_X33_Y10_N30
\inst16~feeder\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst16~feeder_combout\ = VCC

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	combout => \inst16~feeder_combout\);

-- Location: LCCOMB_X33_Y10_N16
\inst14|sub|9~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst14|sub|9~0_combout\ = !\inst14|sub|9~q\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100001111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \inst14|sub|9~q\,
	combout => \inst14|sub|9~0_combout\);

-- Location: IOIBUF_X0_Y11_N8
\CLR~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_CLR,
	o => \CLR~input_o\);

-- Location: CLKCTRL_G2
\CLR~inputclkctrl\ : cycloneive_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \CLR~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \CLR~inputclkctrl_outclk\);

-- Location: FF_X33_Y10_N17
\inst14|sub|9\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst14|sub|9~0_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst14|sub|9~q\);

-- Location: LCCOMB_X33_Y10_N24
\inst14|sub|90\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst14|sub|90~combout\ = \inst14|sub|87~q\ $ (\inst14|sub|9~q\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \inst14|sub|87~q\,
	datad => \inst14|sub|9~q\,
	combout => \inst14|sub|90~combout\);

-- Location: FF_X33_Y10_N25
\inst14|sub|87\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst14|sub|90~combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst14|sub|87~q\);

-- Location: LCCOMB_X33_Y10_N28
\inst14|sub|97\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst14|sub|97~combout\ = \inst14|sub|99~q\ $ (((\inst14|sub|87~q\ & \inst14|sub|9~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst14|sub|87~q\,
	datac => \inst14|sub|99~q\,
	datad => \inst14|sub|9~q\,
	combout => \inst14|sub|97~combout\);

-- Location: FF_X33_Y10_N29
\inst14|sub|99\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst14|sub|97~combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst14|sub|99~q\);

-- Location: LCCOMB_X33_Y10_N8
\inst14|sub|107\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst14|sub|107~combout\ = \inst14|sub|110~q\ $ (((\inst14|sub|9~q\ & (\inst14|sub|99~q\ & \inst14|sub|87~q\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst14|sub|9~q\,
	datab => \inst14|sub|99~q\,
	datac => \inst14|sub|110~q\,
	datad => \inst14|sub|87~q\,
	combout => \inst14|sub|107~combout\);

-- Location: FF_X33_Y10_N9
\inst14|sub|110\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst14|sub|107~combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst14|sub|110~q\);

-- Location: FF_X33_Y10_N31
inst16 : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLK~input_o\,
	d => \inst16~feeder_combout\,
	clrn => \inst14|sub|ALT_INV_110~q\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst16~q\);

-- Location: LCCOMB_X33_Y10_N22
inst18 : cycloneive_lcell_comb
-- Equation(s):
-- \inst18~combout\ = LCELL((\inst16~q\ & \CLK~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \inst16~q\,
	datad => \CLK~input_o\,
	combout => \inst18~combout\);

-- Location: CLKCTRL_G9
\inst18~clkctrl\ : cycloneive_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \inst18~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \inst18~clkctrl_outclk\);

-- Location: IOIBUF_X28_Y0_N22
\s1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_s1,
	o => \s1~input_o\);

-- Location: IOIBUF_X34_Y2_N22
\s0~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_s0,
	o => \s0~input_o\);

-- Location: IOIBUF_X34_Y12_N22
\b1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b1,
	o => \b1~input_o\);

-- Location: LCCOMB_X33_Y4_N4
\inst2|120~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|120~0_combout\ = (\s0~input_o\ & (\s1~input_o\ & \b1~input_o\)) # (!\s0~input_o\ & (!\s1~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100000011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \s0~input_o\,
	datac => \s1~input_o\,
	datad => \b1~input_o\,
	combout => \inst2|120~0_combout\);

-- Location: IOIBUF_X34_Y12_N15
\b2~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b2,
	o => \b2~input_o\);

-- Location: IOIBUF_X34_Y12_N8
\b4~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b4,
	o => \b4~input_o\);

-- Location: IOIBUF_X34_Y9_N15
\b5~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b5,
	o => \b5~input_o\);

-- Location: IOIBUF_X34_Y12_N1
\b6~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b6,
	o => \b6~input_o\);

-- Location: IOIBUF_X32_Y0_N15
\b7~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b7,
	o => \b7~input_o\);

-- Location: LCCOMB_X33_Y4_N14
\inst2|122~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|122~0_combout\ = (\s1~input_o\ & ((\s0~input_o\) # ((\inst2|115~q\)))) # (!\s1~input_o\ & (!\s0~input_o\ & (\inst2|114~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101010011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|114~q\,
	datad => \inst2|115~q\,
	combout => \inst2|122~0_combout\);

-- Location: IOIBUF_X32_Y0_N22
\b8~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b8,
	o => \b8~input_o\);

-- Location: LCCOMB_X33_Y4_N28
\inst2|121~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|121~0_combout\ = (\s1~input_o\ & ((\s0~input_o\ & (\b8~input_o\)) # (!\s0~input_o\ & ((\inst2|114~q\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011100000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \b8~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|114~q\,
	datad => \s1~input_o\,
	combout => \inst2|121~0_combout\);

-- Location: LCCOMB_X33_Y4_N8
\inst2|121~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|121~1_combout\ = (\inst2|121~0_combout\) # ((!\s1~input_o\ & (!\s0~input_o\ & \inst2|113~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|113~q\,
	datad => \inst2|121~0_combout\,
	combout => \inst2|121~1_combout\);

-- Location: FF_X33_Y4_N9
\inst2|113\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst2|121~1_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst2|113~q\);

-- Location: LCCOMB_X33_Y4_N22
\inst2|122~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|122~1_combout\ = (\s0~input_o\ & ((\inst2|122~0_combout\ & (\b7~input_o\)) # (!\inst2|122~0_combout\ & ((\inst2|113~q\))))) # (!\s0~input_o\ & (((\inst2|122~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011110010110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \b7~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|122~0_combout\,
	datad => \inst2|113~q\,
	combout => \inst2|122~1_combout\);

-- Location: FF_X33_Y4_N23
\inst2|114\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst2|122~1_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst2|114~q\);

-- Location: LCCOMB_X33_Y4_N24
\inst2|123~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|123~0_combout\ = (\s1~input_o\ & (\s0~input_o\)) # (!\s1~input_o\ & ((\s0~input_o\ & (\inst2|114~q\)) # (!\s0~input_o\ & ((\inst2|115~q\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101100111001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|114~q\,
	datad => \inst2|115~q\,
	combout => \inst2|123~0_combout\);

-- Location: LCCOMB_X33_Y4_N16
\inst2|123~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|123~1_combout\ = (\s1~input_o\ & ((\inst2|123~0_combout\ & (\b6~input_o\)) # (!\inst2|123~0_combout\ & ((\inst2|116~q\))))) # (!\s1~input_o\ & (((\inst2|123~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101110110100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \b6~input_o\,
	datac => \inst2|116~q\,
	datad => \inst2|123~0_combout\,
	combout => \inst2|123~1_combout\);

-- Location: FF_X33_Y4_N17
\inst2|115\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst2|123~1_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst2|115~q\);

-- Location: LCCOMB_X33_Y4_N26
\inst2|124~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|124~0_combout\ = (\s1~input_o\ & (((\s0~input_o\)))) # (!\s1~input_o\ & ((\s0~input_o\ & (\inst2|115~q\)) # (!\s0~input_o\ & ((\inst2|116~q\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110010111100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \inst2|115~q\,
	datac => \s0~input_o\,
	datad => \inst2|116~q\,
	combout => \inst2|124~0_combout\);

-- Location: LCCOMB_X33_Y4_N2
\inst2|124~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|124~1_combout\ = (\s1~input_o\ & ((\inst2|124~0_combout\ & (\b5~input_o\)) # (!\inst2|124~0_combout\ & ((\inst2|117~q\))))) # (!\s1~input_o\ & (((\inst2|124~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101101011010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \b5~input_o\,
	datac => \inst2|124~0_combout\,
	datad => \inst2|117~q\,
	combout => \inst2|124~1_combout\);

-- Location: FF_X33_Y4_N3
\inst2|116\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst2|124~1_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst2|116~q\);

-- Location: LCCOMB_X33_Y4_N6
\inst2|125~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|125~0_combout\ = (\s0~input_o\ & (((\s1~input_o\)))) # (!\s0~input_o\ & ((\s1~input_o\ & (\inst2|118~q\)) # (!\s1~input_o\ & ((\inst2|117~q\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110001111100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|118~q\,
	datab => \s0~input_o\,
	datac => \s1~input_o\,
	datad => \inst2|117~q\,
	combout => \inst2|125~0_combout\);

-- Location: LCCOMB_X33_Y4_N18
\inst2|125~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|125~1_combout\ = (\s0~input_o\ & ((\inst2|125~0_combout\ & (\b4~input_o\)) # (!\inst2|125~0_combout\ & ((\inst2|116~q\))))) # (!\s0~input_o\ & (((\inst2|125~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \b4~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|116~q\,
	datad => \inst2|125~0_combout\,
	combout => \inst2|125~1_combout\);

-- Location: FF_X33_Y4_N19
\inst2|117\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst2|125~1_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst2|117~q\);

-- Location: IOIBUF_X34_Y7_N8
\b3~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b3,
	o => \b3~input_o\);

-- Location: LCCOMB_X33_Y4_N0
\inst2|126~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|126~0_combout\ = (\s1~input_o\ & ((\s0~input_o\) # ((\inst2|119~q\)))) # (!\s1~input_o\ & (!\s0~input_o\ & ((\inst2|118~q\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011100110101000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|119~q\,
	datad => \inst2|118~q\,
	combout => \inst2|126~0_combout\);

-- Location: LCCOMB_X33_Y4_N12
\inst2|126~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|126~1_combout\ = (\s0~input_o\ & ((\inst2|126~0_combout\ & ((\b3~input_o\))) # (!\inst2|126~0_combout\ & (\inst2|117~q\)))) # (!\s0~input_o\ & (((\inst2|126~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111001110001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|117~q\,
	datab => \s0~input_o\,
	datac => \b3~input_o\,
	datad => \inst2|126~0_combout\,
	combout => \inst2|126~1_combout\);

-- Location: FF_X33_Y4_N13
\inst2|118\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst2|126~1_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst2|118~q\);

-- Location: LCCOMB_X33_Y4_N10
\inst2|127~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|127~0_combout\ = (\s1~input_o\ & ((\s0~input_o\) # ((\inst2|120~q\)))) # (!\s1~input_o\ & (!\s0~input_o\ & (\inst2|119~q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101010011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|119~q\,
	datad => \inst2|120~q\,
	combout => \inst2|127~0_combout\);

-- Location: LCCOMB_X33_Y4_N30
\inst2|127~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|127~1_combout\ = (\s0~input_o\ & ((\inst2|127~0_combout\ & (\b2~input_o\)) # (!\inst2|127~0_combout\ & ((\inst2|118~q\))))) # (!\s0~input_o\ & (((\inst2|127~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1011101111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \b2~input_o\,
	datab => \s0~input_o\,
	datac => \inst2|118~q\,
	datad => \inst2|127~0_combout\,
	combout => \inst2|127~1_combout\);

-- Location: FF_X33_Y4_N31
\inst2|119\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst2|127~1_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst2|119~q\);

-- Location: LCCOMB_X33_Y4_N20
\inst2|120~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|120~1_combout\ = (\s1~input_o\ & (\inst2|120~0_combout\)) # (!\s1~input_o\ & ((\inst2|120~0_combout\ & (\inst2|120~q\)) # (!\inst2|120~0_combout\ & ((\inst2|119~q\)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101100111001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \s1~input_o\,
	datab => \inst2|120~0_combout\,
	datac => \inst2|120~q\,
	datad => \inst2|119~q\,
	combout => \inst2|120~1_combout\);

-- Location: FF_X33_Y4_N21
\inst2|120\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \inst18~clkctrl_outclk\,
	d => \inst2|120~1_combout\,
	clrn => \CLR~inputclkctrl_outclk\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst2|120~q\);

-- Location: IOIBUF_X34_Y18_N1
\a7~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a7,
	o => \a7~input_o\);

-- Location: IOIBUF_X34_Y9_N8
\a6~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a6,
	o => \a6~input_o\);

-- Location: IOIBUF_X1_Y0_N22
\a8~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a8,
	o => \a8~input_o\);

-- Location: IOIBUF_X16_Y24_N8
\a5~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a5,
	o => \a5~input_o\);

-- Location: IOIBUF_X23_Y24_N8
\a2~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a2,
	o => \a2~input_o\);

-- Location: IOIBUF_X3_Y0_N1
\a3~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a3,
	o => \a3~input_o\);

-- Location: IOIBUF_X30_Y24_N1
\a4~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a4,
	o => \a4~input_o\);

-- Location: IOIBUF_X23_Y24_N15
\a1~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_a1,
	o => \a1~input_o\);

ww_q1 <= \q1~output_o\;

ww_q2 <= \q2~output_o\;

ww_q3 <= \q3~output_o\;

ww_q4 <= \q4~output_o\;

ww_q6 <= \q6~output_o\;

ww_q7 <= \q7~output_o\;

ww_q8 <= \q8~output_o\;

ww_q9 <= \q9~output_o\;

ww_q10 <= \q10~output_o\;

ww_q11 <= \q11~output_o\;

ww_q12 <= \q12~output_o\;

ww_q13 <= \q13~output_o\;

ww_q14 <= \q14~output_o\;

ww_q15 <= \q15~output_o\;

ww_q16 <= \q16~output_o\;

ww_q5 <= \q5~output_o\;
END structure;


