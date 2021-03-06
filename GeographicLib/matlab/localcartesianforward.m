function localcartesianforward(~, ~, ~, ~)
%localcartesianforward  Convert geographic coordinates to local cartesian
%
%   [cartesian, rot] = localcartesianforward(origin, geodetic)
%   [cartesian, rot] = localcartesianforward(origin, geodetic, a, f)
%
%   origin is a 1 x 3 or 1 x 2 matrix
%       lat0 = origin(1,1) in degrees
%       lon0 = origin(1,2) in degrees
%       h0 = origin(1,3) in meters (default 0 m)
%   geodetic is an M x 3 or M x 2 matrix of geodetic coordinates
%       lat = geodetic(:,1) in degrees
%       lon = geodetic(:,2) in degrees
%       h = geodetic(:,3) in meters (default 0 m)
%
%   cartesian is an M x 3 matrix of local cartesian coordinates
%       x = cartesian(:,1) in meters
%       y = cartesian(:,2) in meters
%       z = cartesian(:,3) in meters
%   rot is an M x 9 matrix
%       M = rot(:,1:9) rotation matrix in row major order.  Pre-multiplying
%           a unit vector in local cartesian coordinates at (lat, lon, h)
%           by M transforms the vector to local cartesian coordinates at
%           (lat0, lon0, h0)
%
%   a = major radius (meters)
%   f = flattening (0 means a sphere)
%   If a and f are omitted, the WGS84 values are used.
%
% This is an interface to the GeographicLib C++ routine
%     LocalCartesian::Forward
% See the documentation on this function for more information:
% http://geographiclib.sf.net/html/classGeographicLib_1_1LocalCartesian.html
  error('Error: executing .m file instead of compiled routine');
end
% localcartesianforward.m
% Matlab .m file for geographic to local cartesian conversions
%
% Copyright (c) Charles Karney (2011) <charles@karney.com> and licensed under
% the MIT/X11 License.  For more information, see
% http://geographiclib.sourceforge.net/
