#!/usr/bin/env python
# -*- coding: utf-8 -*-

import logging
import Artus.Utility.logger as logger
log = logging.getLogger(__name__)

import argparse
import copy
import os

import Artus.Utility.jsonTools as jsonTools
import Artus.HarryPlotter.harry as harry


if __name__ == "__main__":

	parser = argparse.ArgumentParser(description="Make screening strength plots.",
	                                 parents=[logger.loggingParser])

	parser.add_argument("-s", "--screening-strengths", nargs="+", default=[0.99, 0.995],
	                    help="Screening strength values.")
	
	parser.add_argument("--temp-range-bins", default="100,50,150",
	                    help="Binning for axes showing the temperature range.")
	parser.add_argument("--temp-rate-bins", default="100,2,6",
	                    help="Binning for axes showing the temperature rate of change.")
	parser.add_argument("--n-cycles-bins", default="100,0,40",
	                    help="Binning for axes showing the number of cycles.")
	parser.add_argument("--time-test-bins", default="100,0,48",
	                    help="Binning for axes showing the test time.")
	
	parser.add_argument("-a", "--args", default=" --plot-modules PlotRoot",
	                    help="Additional Arguments for HarryPlotter. [Default: %(default)s]")
	parser.add_argument("-n", "--n-processes", type=int, default=1,
	                    help="Number of (parallel) processes. [Default: %(default)s]")
	parser.add_argument("-f", "--n-plots", type=int,
	                    help="Number of plots. [Default: all]")
	parser.add_argument("-o", "--output-dir", default="output",
	                    help="Output directory. [Default: %(default)s]")

	args = parser.parse_args()
	logger.initLogger(args)
	
	screening_strength_strings = [str(s) for s in args.screening_strengths]
	
	plots = [
		"thermal_cycling_screening_strength",
	]
	plot_configs = {}
	for plot in plots:
		plot_configs[plot] = jsonTools.JsonDict(os.path.join("plots", plot+".json"))
		plot_configs[plot]["output_dir"] = args.output_dir
	
	plot_configs["thermal_cycling_screening_strength"]["x_bins"] = args.n_cycles_bins
	plot_configs["thermal_cycling_screening_strength"]["y_bins"] = args.temp_rate_bins
	
	plots_per_ss = [
		"thermal_cycling_number_cycles",
		"thermal_cycling_test_time",
	]
	plot_configs_per_ss = {}
	for plot in plots_per_ss:
		for screening_strength, screening_strength_string in zip(args.screening_strengths, screening_strength_strings):
			
			plot_configs_per_ss.setdefault(plot, {})[screening_strength_string] = jsonTools.JsonDict(os.path.join("plots", plot+".json"))
			plot_configs_per_ss[plot][screening_strength_string]["x_expressions"] = [x.replace("0.01", str(1.0-screening_strength)) for x in plot_configs_per_ss[plot][screening_strength_string]["x_expressions"]]
			plot_configs_per_ss[plot][screening_strength_string]["title"] = plot_configs_per_ss[plot][screening_strength_string]["title"].replace("1%", str((1.0-screening_strength) * 100.0)+"%")
			plot_configs_per_ss[plot][screening_strength_string]["output_dir"] = os.path.join(args.output_dir, "screening_strength_"+screening_strength_string)
	
	for plot_config in plot_configs_per_ss["thermal_cycling_number_cycles"].values():
		plot_config["x_bins"] = args.temp_range_bins
		plot_config["y_bins"] = args.temp_rate_bins
	for plot_config in plot_configs_per_ss["thermal_cycling_test_time"].values():
		plot_config["x_bins"] = args.temp_range_bins
		plot_config["y_bins"] = args.temp_rate_bins
	
	list_of_config_dicts = plot_configs.values()
	for tmp_plot_configs_per_ss in plot_configs_per_ss.values():
		list_of_config_dicts.extend(tmp_plot_configs_per_ss.values())
	
	if log.isEnabledFor(logging.DEBUG):
		import pprint
		pprint.pprint(list_of_config_dicts)

	harry.HarryPlotter(
			list_of_config_dicts=list_of_config_dicts,
			list_of_args_strings=[args.args],
			n_processes=args.n_processes,
			n_plots=args.n_plots
	)

