/*
 * Scriptographer
 *
 * This file is part of Scriptographer, a Plugin for Adobe Illustrator.
 *
 * Copyright (c) 2002-2007 Juerg Lehni, http://www.scratchdisk.com.
 * All rights reserved.
 *
 * Please visit http://scriptographer.com/ for updates and contact.
 *
 * -- GPL LICENSE NOTICE --
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * -- GPL LICENSE NOTICE --
 * 
 * File created on Apr 10, 2007.
 *
 * $Id: $
 */

package com.scratchdisk.script.rhino;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;
import org.mozilla.javascript.Wrapper;

import com.scratchdisk.list.AbstractMap;

/**
 * MapAdapter wraps a Rhino ScriptableObject instance in a Map interface.
 * All methods are implemented, even entrySet() / keySet()
 * This is the opposite of {@link MapWrapper}.
 * 
 * @author lehni
 */
public class MapAdapter extends AbstractMap {
	Scriptable object;
	
	public MapAdapter(Scriptable object) {
		this.object = object;
	}

	protected Object[] keys() {
		return object.getIds();
	}

	public Object get(Object key) {
		Object value;
		if (key instanceof Integer)
			value = ScriptableObject.getProperty(object, ((Integer) key).intValue());
		else if (key instanceof String)
			value = ScriptableObject.getProperty(object, (String) key);
		else
			value = null;
		if (value instanceof Wrapper)
			value = ((Wrapper) value).unwrap();
		else if (value == ScriptableObject.NOT_FOUND)
			value = null;
		return value;
	}

	public Object put(Object key, Object value) {
		// Wrap the value if it is not already
		if (value != null && !(value instanceof Scriptable)) {
			Context cx = Context.getCurrentContext();
			value = cx.getWrapFactory().wrap(cx, object, value, value.getClass());
		}
		Object prev = get(key);
		if (key instanceof Integer)
			object.put(((Integer) key).intValue(), object, value);
		else if (key instanceof String)
			object.put((String) key, object, value);
		else
			prev = null;
		return prev;
	}

	public Object remove(Object key) {
		if (containsKey(key)) {
			Object prev = get(key);
			if (key instanceof Integer)
				object.delete(((Integer) key).intValue());
			else if (key instanceof String)
				object.delete((String) key);
			return prev;
		}
		return null;
	}

	public boolean containsKey(Object key) {
		if (key instanceof Integer)
			return object.has(((Integer) key).intValue(), object);
		else if (key instanceof String)
			return object.has((String) key, object);
		else
			return false;
	}
}
