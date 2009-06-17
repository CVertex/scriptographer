/**
 * JavaScript Doclet
 * (c) 2005 - 2009, Juerg Lehni, http://www.scratchdisk.com
 *
 * Doclet.js is released under the MIT license
 * http://dev.scriptographer.com/ 
 */

/**
 * A virtual field that unifies getter and setter functions, just like Rhino does
 */
BeanProperty = SyntheticField.extend({
	initialize: function(classObject, name, getter, setters) {
		this.base(classObject, name, getter); // this.member is the getter
		this.setters = setters;
		// Set setter to the one with the documentation, so isVisible uses it too
		this.setter = setters && (setters.members.find(function(member) {
			var tags = member.inlineTags();
			if (tags.length)
				return member;
		}) || setters.members.first);

		var tags = getter.inlineTags();
		// Use the setter that was found to have documentation in the loop above
		if (!tags.length && this.setter)
			tags = this.setter.inlineTags();

		this.seeTagList = [];
		this.inlineTagList = [];
		if (!this.setter)
			this.inlineTagList.push(new Tag('Read-only. '))
		this.inlineTagList.append(tags);
	},

	firstSentenceTags: function() {
		return this.inlineTagList;
	},

	inlineTags: function() {
		return this.inlineTagList;
	},

	seeTags: function() {
		return this.seeTagList;
	},

	getVisible: function() {
		// SG Convention: Hide read-only is-getter beans and show is-method instead.
		if (/^is/.test(this.member.name()) && !this.setters)
			return false;
		return this.base() && (!this.setters || Member.isVisible(this.setter));
	},

	statics: {
		isGetter: function(method) {
			// As a convention, only add non static bean properties to
			// the documentation. static properties are all supposed to
			// be uppercae and constants.
			return method.parameters().length == 0 && !method.isStatic()
				&& method.returnType().typeName() != 'void';
		},

		isSetter: function(method, type, conversion) {
			var params = method.parameters(), typeClass, paramName;
			var param = params.length == 1 && params[0];
			return !method.isStatic()
				&& method.returnType().typeName() == 'void' && params.length == 1
				&& (!type
					|| params[0].typeName() == type.typeName()
					// TODO: checking both hasSuperclass and hasInterface is necessary to simulate isAssignableFrom
					// Think of adding this to Type, and calling it here
					|| conversion && (typeClass = type.asClassDoc())
						&& (paramName = params[0].paramType().qualifiedName())
						&& (typeClass.hasSuperclass(paramName) || typeClass.hasInterface(paramName)));
		}
	}
});