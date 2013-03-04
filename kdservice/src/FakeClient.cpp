/*
 * FakeClient.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/FakeClient.h"

namespace Debugger {

FakeClient::FakeClient() :
		pStateMachine(0) {
}

FakeClient::~FakeClient() {
}

void FakeClient::connect() {

}

void FakeClient::attachKenel(const std::string& parameters) {

}

void FakeClient::disconnect() {

}

void FakeClient::setTargetStateMachine(StateMachine* pStateMachine) {
	this->pStateMachine = pStateMachine;
}

const States::TargetStateInfo FakeClient::getTargetStateInfo() const {
	return pStateMachine->getTargetStateInfo();
}

} /* namespace Debugger */
