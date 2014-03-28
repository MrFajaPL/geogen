﻿using System;

namespace GeoGen.Studio.PlugInLoader
{
    /// <summary>
    /// Specifies whether creation of multiple plug-in instances is allowed in case plug-in's <see cref="Registrator"/>s is called with multiple parameter combinations.
    /// </summary>
    public enum InstanceCountMode{
        /// <summary>
        /// Create one plug-in instance only and call the <see cref="Registrator"/>s on it.
        /// </summary>
        One,
        /// <summary>
        /// Create a new plug-in instance for each <see cref="Registrator"/> call.
        /// </summary>
        OnePerRegistration
    };

    /// <summary>
    /// Attribute specifying how <see cref="OldLoader"/> handles the plug-in.
    /// </summary>
    [AttributeUsage(AttributeTargets.Class, Inherited = true, AllowMultiple = false)]
    public sealed class PlugInAttribute : Attribute
    {
        /// <summary>
        /// User-friendly name of the plug-in.
        /// </summary>
        /// <value>The name.</value>
        public string Name { get; set; }

        /// <summary>
        /// Short description of the plug-in.
        /// </summaisry>
        /// <value>The description.</value>
        public string Description { get; set; }
        
        /// <summary>
        /// Specifies whether creation of multiple plug-in instances is allowed in case plug-in's <see cref="Registrator"/>s is called with multiple parameter combinations.
        /// </summary>
        public InstanceCountMode InstanceCountMode { get; set; }

        /// <summary>
        /// True if this plug-in is showing in plug-in lists.
        /// </summary>
        public bool VisibleInList { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="PlugInAttribute"/> class.
        /// </summary>        
        /// <param name="name">User-friendly name of the plug-in</param>
        /// <param name="description">Short user-friendly description of the plug-in</param>        
        /// <param name="instanceCountMode">Specifies whether creation of multiple plug-in instances is allowed in case plug-in's <see cref="Registrator"/>s is called with multiple parameter combinations.</param>
        public PlugInAttribute(string name = "", string description = "", InstanceCountMode instanceCountMode = InstanceCountMode.One, bool visibleInList = true)
        {
            this.Name = name;
            this.Description = description;
            this.InstanceCountMode = instanceCountMode;
            this.VisibleInList = visibleInList;
        }
    }
}