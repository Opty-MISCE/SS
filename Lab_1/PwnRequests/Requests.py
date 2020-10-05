#!/usr/bin/env python
import requests
from re import findall

HELLO = "http://mustard.stt.rnl.tecnico.ulisboa.pt:15002/hello"
MORE = "http://mustard.stt.rnl.tecnico.ulisboa.pt:15002/more"
FINISH = "http://mustard.stt.rnl.tecnico.ulisboa.pt:15002/finish"

session = requests.session()
trg, crr = findall(r"\d+", session.get(HELLO).text)[:2]

while crr != trg:
    crr = findall(r"\d+", session.get(MORE).text)[-1]

print(session.get(FINISH).text)
session.close()
