/*******************************************************************************
 * Copyright (c) 2004 IBM Corporation and others.
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/cpl-v10.html
 * 
 * Contributors:
 *     IBM Corporation - initial API and implementation
 *     Bjorn Freeman-Benson - initial API and implementation
 *******************************************************************************/
package com.tuxford.wkd.launch.cfg;

/**
 * Constants for the PDA debugger.
 */
public interface IWkdConstants {
	
	/**
	 * Unique identifier for the PDA debug model (value 
	 * <code>org.eclipse.debug.examples.pda</code>).
	 */
	public static final String ID_PDA_DEBUG_MODEL = "org.eclipse.debug.examples.pda";
	
	/**
	 * Name of the string substitution variable that resolves to the
	 * location of a local Perl executable (value <code>perlExecutable</code>).
	 */
	public static final String ID_PERL_EXECUTABLE = "perlExecutable"; //Should be removed in release
	
		
	/**
	 * Launch configuration key. Value is a path to a perl
	 * program. The path is a string representing a full path
	 * to a perl program in the workspace. 
	 */
	public static final String ATTR_PDA_PROGRAM = ID_PDA_DEBUG_MODEL + ".ATTR_PDA_PROGRAM";
}
