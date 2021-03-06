import ROOT
import pyWIMP.DMModels.base_model as base_model
from pyWIMP.DMModels.tritium_decay_model import TritiumDecayModel
from pyWIMP.DMModels.gaussian_signal import GaussianSignalModel
import sys
import pyWIMP.WIMPPdfs as pdfs  
from pyWIMP.utilities.utilities import rescale_frame
import math


ROOT.gROOT.SetBatch()
exposure_time_in_days = 5
time_in_days = 10*365.25
kg = 30 
upper_energy = 20
lower_energy = 0.5
axion_mass = 0.3

basevars = base_model.BaseVariables(5,time_in_days/365.25, lower_energy, upper_energy)
time = basevars.get_time()
energy = basevars.get_energy()
energy.setBins(64)
time.setBins(64)

tritium_decay = TritiumDecayModel(basevars, exposure_time_in_days, 200, kg, 0.001)

total_background = tritium_decay.get_model() 

total_background.getVariables().writeToStream(ROOT.cout, False)

data = total_background.generate(ROOT.RooArgSet(energy, time))

total_background.fitTo(data)

c1 = ROOT.TCanvas()
for var in [energy, time]:
    frame = var.frame()
    data.plotOn(frame)
    total_background.plotOn(frame)
    total_background.plotOn(frame, ROOT.RooFit.Components("*flat_extend*"), ROOT.RooFit.LineStyle(ROOT.kDashed))
    frame.Draw()
    bin_width = frame.getFitRangeBinW()
    axis = rescale_frame(c1, frame, 1./(bin_width*time_in_days*kg), "Events/keV/kg/d") 
    c1.Update()
    raw_input("E")


wimpClass = GaussianSignalModel(basevars,
                                mean_of_signal=axion_mass)

model_normal = ROOT.RooRealVar("model_normal", 
                               "Counts", 
                               0, -10, 1000)
model = wimpClass.get_model()
norm = wimpClass.get_normalization()*model.getNorm(
       ROOT.RooArgSet(basevars.get_energy())) 
print axion_mass, upper_energy, lower_energy
print norm

