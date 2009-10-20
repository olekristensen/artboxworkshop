attribute float partSize;

void main(void)
{
	vec4 eyeCoord = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = gl_ProjectionMatrix * eyeCoord;
	float dist = distance(eyeCoord, vec4(0.0, 0.0, 0.0, 1.0));
	float att = sqrt(1.0 / (gl_Point.distanceConstantAttenuation +
	(gl_Point.distanceLinearAttenuation +
	gl_Point.distanceQuadraticAttenuation * dist) * dist));
	float size = partSize * att;
	gl_PointSize = size;
	float fade;// = min(size, gl_Point.fadeThresholdSize) / gl_Point.fadeThresholdSize;
	if(size < 10.0){
		fade = size / 10.0;
	} else {
		fade = 1.0;
	}
	fade = fade * fade * gl_Color.a;
	gl_FrontColor = vec4(gl_Color.rgb, fade);
}



