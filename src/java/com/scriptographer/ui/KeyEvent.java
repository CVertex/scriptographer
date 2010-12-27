/*
 * Scriptographer
 *
 * This file is part of Scriptographer, a Scripting Plugin for Adobe Illustrator
 * http://scriptographer.org/
 *
 * Copyright (c) 2002-2010, Juerg Lehni
 * http://scratchdisk.com/
 *
 * All rights reserved. See LICENSE file for details.
 * 
 * File created on Feb 9, 2010.
 */

package com.scriptographer.ui;

import com.scratchdisk.util.IntegerEnumUtils;
import com.scriptographer.ScriptographerEngine;
import com.scriptographer.script.EnumUtils;
import com.scriptographer.sg.Event;

/**
 * The KeyEvent object is received by the key event handlers
 * {@code onKeyDown(event)} and {@code onKeyUp(event)}. The KeyEvent
 * object is the only parameter passed to these functions and contains
 * information about the key event.
 * 
 * Sample code:
 * <code>
 * function onKeyDown(event) {
 * 	// The character of the key that was pressed
 * 	print(event.character);
 * }
 * </code>
 * 
 * @author lehni
 */
public class KeyEvent extends Event {

	private KeyCode keyCode;
	private char character;
	private KeyEventType type;

	/**
	 * @jshide
	 */
	public KeyEvent(int type, int keyCode, char character, int modifiers) {
		super(modifiers);
		this.type = type == ScriptographerEngine.EVENT_KEY_DOWN
			? KeyEventType.KEY_DOWN : KeyEventType.KEY_UP;
		this.keyCode = IntegerEnumUtils.get(KeyCode.class, keyCode);
		this.character = character;
	}

	/**
	 * Specifies the type of key event.
	 * 
	 * @return the type of key event.
	 */
	public KeyEventType getType() {
		return type;
	}

	/**
	 * Specifies the virtual key code of the key that caused this key event.
	 * 
	 * @return the virtual key code.
	 */
	public KeyCode getKeyCode() {
		return keyCode;
	}

	/**
	 * Specifies the {@code String} character of the key that caused this
	 * key event.
	 * 
	 * @return the key character.
	 */
	public char getCharacter() {
		return character;
	}

	public String toString() {
		StringBuffer buf = new StringBuffer();
		buf.append("{ type: ").append(EnumUtils.getScriptName(type));
		buf.append(", keyCode: ").append(keyCode);
		buf.append(", character: ").append(character);
		buf.append(", modifiers: ").append(getModifiers());
		buf.append(" }");
		return buf.toString();
	}
}
