using ReactNative.Bridge;
using System;
using System.Collections.Generic;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;

namespace Payfubao.RNPayfubao
{
    /// <summary>
    /// A module that allows JS to share data.
    /// </summary>
    class RNPayfubaoModule : NativeModuleBase
    {
        /// <summary>
        /// Instantiates the <see cref="RNPayfubaoModule"/>.
        /// </summary>
        internal RNPayfubaoModule()
        {

        }

        /// <summary>
        /// The name of the native module.
        /// </summary>
        public override string Name
        {
            get
            {
                return "RNPayfubao";
            }
        }
    }
}
